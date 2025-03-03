#ifndef HTTP_REQUEST_MANAGER_H
#define HTTP_REQUEST_MANAGER_H

#include "http_request_task.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMap>

class Http_Request_Manager : public QObject {
    Q_OBJECT
public:
    static Http_Request_Manager* getInstance(QObject* parent = nullptr);
    ~Http_Request_Manager();

    void sendRequest(const Http_Request_Task& task,
                     std::function<void(const QByteArray&)> callbackNormal,
                     std::function<void(const QByteArray&)> callbackError,
                     std::function<void(int)> callbackProgress = nullptr);

    void setServerAddress(const QString& newServerAddress);

private:
    Http_Request_Manager(QObject* parent = nullptr);

    QUrl constructURL(const QString& api, const QUrlQuery& query);
    void setSSLConfig();
    QNetworkReply* sendGetRequest(const QNetworkRequest& request);
    QNetworkReply* sendPostRequest(const QNetworkRequest& request, const QByteArray& data);
    QNetworkReply* sendFileRequest(const QNetworkRequest& request, const QString& filePath);
    QString handleNetworkError(QNetworkReply::NetworkError code);

    static Http_Request_Manager* m_gInstance;
    QNetworkAccessManager* m_pSharedNAM = nullptr;
    QString m_sServerAddress;
    QMap<QNetworkReply*, QPair<std::function<void(const QByteArray&)>,
                                std::function<void(const QByteArray&)>>> m_mReplyCallbacks;
};

#endif // HTTP_REQUEST_MANAGER_H
