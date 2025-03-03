#include "http_api_manager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "ThreadPool.h"
#include "Logger.h"

// 定义私有类
class Http_Api_Manager::Private {
public:
    Private() : threadPool(std::make_unique<ThreadPool>(40)) {}
    std::unique_ptr<ThreadPool> threadPool;
};

// 初始化静态成员
Http_Api_Manager* Http_Api_Manager::m_gInstance = nullptr;

// 单例获取方法
Http_Api_Manager* Http_Api_Manager::getInstance(QObject* parent)
{
    if (!m_gInstance) {
        m_gInstance = new Http_Api_Manager(parent);
    }
    return m_gInstance;
}

// 构造函数
Http_Api_Manager::Http_Api_Manager(QObject* parent)
    : QObject(parent), d(std::make_unique<Private>())
{
}


// 析构函数
Http_Api_Manager::~Http_Api_Manager() = default;


void Http_Api_Manager::requestApiData(ApiType apiType, const Http_Request_Task& task,
                                      QObject* receiver,
                                      std::function<void(const QJsonDocument&)> successCallback,
                                      std::function<void(const QString&)> errorCallback ,
                                      std::function<void(int)> progressCallback) {
    Http_Request_Manager::getInstance()->sendRequest(
        task,
        [this, successCallback](const QByteArray& response) {
            // 在线程池中处理响应
            d->threadPool->enqueue([successCallback, response]() {
                QJsonDocument doc = QJsonDocument::fromJson(response);
                if (successCallback) {
                    successCallback(doc);
                }
            });
        },
        [this, errorCallback](const QByteArray& error) {
            if (errorCallback) {
                // 在线程池中处理错误
                d->threadPool->enqueue([errorCallback, error]() {
                    QString errorStr = QString::fromUtf8(error);
                    errorCallback(errorStr);
                });
            }
        },
        [progressCallback](int progress) {
            // 直接调用进度回调
            if (progressCallback) {
                progressCallback(progress);
            }
        }
        );
}


// 处理正常响应
void Http_Api_Manager::processNormalResponse(const QByteArray& response,
                                             std::function<void(const QJsonDocument&)> callbackHandle)
{
    QJsonDocument doc = QJsonDocument::fromJson(response);
    if (doc.isNull()) {
        return;
    }
    callbackHandle(doc);
}

// 处理错误响应
void Http_Api_Manager::processErrorResponse(const QByteArray& response,
                                            std::function<void(const QString&)> callbackHandle)
{
    callbackHandle(QString(response));
}

