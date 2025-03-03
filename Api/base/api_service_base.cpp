#include "api_service_base.h"
#include "Logger.h"
ApiServiceBase::ApiServiceBase(QObject* parent)
    : QObject(parent), m_handler(nullptr) {}

ApiServiceBase::~ApiServiceBase() {
    delete m_handler;  // 清理响应处理器
}

void ApiServiceBase::setResponseHandler(ApiResponseHandler* handler) {
    m_handler = handler;
}

void ApiServiceBase::sendApiRequest(ApiType apiType, const Http_Request_Task& task) {
    Http_Api_Manager::getInstance()->requestApiData(
        apiType,
        task,
        this,
        [this](const QJsonDocument& doc) { this->onRequestSuccess(doc); },
        [this](const QString& error) { this->onRequestError(error); },
        [this](int progress) { this->onRequestProgress(progress); }
        );
}

// Add these protected slots to ApiServiceBase.h and implement them
void ApiServiceBase::onRequestSuccess(const QJsonDocument &doc) {
    LogInfo << "ApiServiceBase :: onRequestSuccess";
    if (m_handler) {
        m_handler->handleSuccess(doc);
    }
    emit requestSuccess(doc);
}

void ApiServiceBase::onRequestError(const QString &error) {
    LogInfo << "ApiServiceBase :: onRequestError";
    if (m_handler) {
        m_handler->handleError(error);
    }
    emit requestError(error);
}

void ApiServiceBase::onRequestProgress(int progress) {
    LogInfo << "ApiServiceBase :: onRequestProgress";
    if (m_handler) {
        m_handler->handleProgress(progress);
    }
    emit requestProgress(progress);
}

