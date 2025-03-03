#include "http_request_manager.h"
#include <QFile>
#include <QFileInfo>
#include <QUrlQuery>
#include <QHttpMultiPart>

// 初始化静态成员
Http_Request_Manager* Http_Request_Manager::m_gInstance = nullptr;

// 构造函数
Http_Request_Manager::Http_Request_Manager(QObject *parent)
    : QObject{parent}
{
    m_pSharedNAM = new QNetworkAccessManager(this);
    setSSLConfig();
}

// 析构函数
Http_Request_Manager::~Http_Request_Manager()
{
    delete m_pSharedNAM;
}

// 单例获取方法
Http_Request_Manager* Http_Request_Manager::getInstance(QObject *parent)
{
    if (!m_gInstance) {
        m_gInstance = new Http_Request_Manager(parent);
    }
    return m_gInstance;
}

// 发送 HTTP 请求
void Http_Request_Manager::sendRequest(const Http_Request_Task &task,
                                       std::function<void(const QByteArray&)> callbackNormal,
                                       std::function<void(const QByteArray&)> callbackError,
                                       std::function<void(int)> callbackProgress)
{
    // 构造查询参数
    QUrlQuery query;
    for (auto it = task.params().constBegin(); it != task.params().constEnd(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }

    // 构造 URL 和请求
    QUrl url = constructURL(task.api(), query);
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::HTTP2AllowedAttribute, true); // 启用 HTTP/2
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true); // 启用 Pipelining

    QNetworkReply* reply = nullptr;

    // 根据请求类型发送不同的请求
    switch (task.type()) {
    case Http_Request_Task::GET:
        reply = sendGetRequest(request);
        break;
    case Http_Request_Task::POST:
        reply = sendPostRequest(request, task.data());
        break;
    case Http_Request_Task::POST_FILE:
        reply = sendFileRequest(request, QString(task.data()));
        break;
    }

    if (reply) {
        // 存储回调函数
        m_mReplyCallbacks.insert(reply, qMakePair(callbackNormal, callbackError));

        // 处理响应
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray responseData = reply->readAll();
                if (m_mReplyCallbacks.contains(reply)) {
                    m_mReplyCallbacks[reply].first(responseData); // 调用正常回调
                    m_mReplyCallbacks.remove(reply);
                }
            } else {
                QString errorMessage = handleNetworkError(reply->error());
                if (m_mReplyCallbacks.contains(reply)) {
                    m_mReplyCallbacks[reply].second(errorMessage.toUtf8()); // 调用错误回调
                    m_mReplyCallbacks.remove(reply);
                }
            }
            reply->deleteLater();
        });

        // 处理进度回调（如果提供）
        if (callbackProgress) {
            connect(reply, &QNetworkReply::uploadProgress, this, [callbackProgress](qint64 bytesSent, qint64 bytesTotal) {
                if (bytesTotal > 0) {
                    callbackProgress(static_cast<int>((bytesSent * 100) / bytesTotal));
                }
            });
            connect(reply, &QNetworkReply::downloadProgress, this, [callbackProgress](qint64 bytesReceived, qint64 bytesTotal) {
                if (bytesTotal > 0) {
                    callbackProgress(static_cast<int>((bytesReceived * 100) / bytesTotal));
                }
            });
        }
    }
}

// 设置服务器地址
void Http_Request_Manager::setServerAddress(const QString &newServerAddress)
{
    m_sServerAddress = newServerAddress;
}

// 构造完整的 URL
QUrl Http_Request_Manager::constructURL(const QString &api, const QUrlQuery &query)
{
    QUrl url(QString("http://%1").arg(m_sServerAddress) + api);
    url.setQuery(query);
    return url;
}

// 设置 SSL 配置
void Http_Request_Manager::setSSLConfig()
{
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone); // 忽略证书验证（仅用于测试）
    QSslConfiguration::setDefaultConfiguration(sslConfig);
}

// 发送 GET 请求
QNetworkReply* Http_Request_Manager::sendGetRequest(const QNetworkRequest &request)
{
    return m_pSharedNAM->get(request);
}

// 发送 POST 请求
QNetworkReply* Http_Request_Manager::sendPostRequest(const QNetworkRequest &request, const QByteArray &data)
{
    QNetworkRequest postRequest(request);
    postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return m_pSharedNAM->post(postRequest, data);
}

// 发送文件上传请求
QNetworkReply* Http_Request_Manager::sendFileRequest(const QNetworkRequest &request, const QString &filePath)
{
    QFile* file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        delete file;
        return nullptr;
    }

    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QString("form-data; name=\"file\"; filename=\"%1\"")
                           .arg(QFileInfo(*file).fileName()));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    QNetworkRequest fileRequest(request);
    fileRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                          "multipart/form-data; boundary=" + multiPart->boundary());
    QNetworkReply* reply = m_pSharedNAM->post(fileRequest, multiPart);
    multiPart->setParent(reply);
    return reply;
}

// 处理网络错误
QString Http_Request_Manager::handleNetworkError(QNetworkReply::NetworkError code)
{
    QString error = tr("服务器反馈:");
    switch (code) {
    case QNetworkReply::ConnectionRefusedError:
        error += tr("连接被拒绝,请重试");
        break;
    case QNetworkReply::HostNotFoundError:
        error += tr("主机未找到,请检查服务器状态");
        break;
    case QNetworkReply::TimeoutError:
        error += tr("请求超时,请重试");
        break;
    case QNetworkReply::SslHandshakeFailedError:
        error += tr("SSL握手失败,请重试");
        break;
    case QNetworkReply::ContentNotFoundError:
        error += tr("内容未找到,请联系管理员");
        break;
    case QNetworkReply::ServiceUnavailableError:
        error += tr("服务不可用,请联系管理员");
        break;
    default:
        error += tr("未知错误,请联系管理员");
        break;
    }
    return error;
}
