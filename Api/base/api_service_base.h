#ifndef API_SERVICE_BASE_H
#define API_SERVICE_BASE_H

#include "api_response_handler.h"
#include "http_api_manager.h"
// api_service_base.h
class ApiServiceBase : public QObject {
    Q_OBJECT
public:
    explicit ApiServiceBase(QObject* parent = nullptr);
    virtual ~ApiServiceBase();
    void setResponseHandler(ApiResponseHandler* handler);//设置响应处理器
    void sendApiRequest(ApiType apiType, const Http_Request_Task& task);//设置请求

protected slots:
    void onRequestSuccess(const QJsonDocument &doc);
    void onRequestError(const QString &error);
    void onRequestProgress(int progress);

signals:
    void requestSuccess(const QJsonDocument& doc);
    void requestError(const QString& error);
    void requestProgress(int progress);

protected:
    ApiResponseHandler* m_handler = nullptr;
};

#endif // API_SERVICE_BASE_H
