#ifndef API_RESPONSE_HANDLER_H
#define API_RESPONSE_HANDLER_H

#include <QJsonDocument>
#include <QObject>

class ApiResponseHandler : public QObject{
    Q_OBJECT
public:
    ApiResponseHandler(QObject *parent = nullptr){};
    virtual ~ApiResponseHandler() = default; // Virtual destructor for polymorphism

    // Pure virtual methods for response handling
    virtual void handleSuccess(const QJsonDocument& doc) = 0; // Success response
    virtual void handleError(const QString& error) = 0;       // Error response
    virtual void handleProgress(int progress) = 0;            // Progress updates
};

#endif // API_RESPONSE_HANDLER_H
