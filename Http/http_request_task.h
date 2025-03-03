#ifndef HTTP_REQUEST_TASK_H
#define HTTP_REQUEST_TASK_H

#include <QMap>
#include <QByteArray>
#include <QObject>

class Http_Request_Task {
public:
    enum RequestType {
        GET,        // Standard GET request
        POST,       // Standard POST request with data
        POST_FILE   // POST request for file uploads
    };

    // Constructor to initialize the task
    Http_Request_Task(RequestType type, const QString& api,
                      const QMap<QString, QString>& params = {},
                      const QByteArray& data = {})
        :m_type(type),m_api(api),m_params(params),m_data(data)
    {

    }

    // Getters for task properties
    RequestType type() const { return m_type; }
    QString api() const { return m_api; }
    QMap<QString, QString> params() const { return m_params; }
    QByteArray data() const { return m_data; }

private:
    RequestType m_type;              // Type of HTTP request
    QString m_api;                   // API endpoint
    QMap<QString, QString> m_params; // Query parameters
    QByteArray m_data;               // Request body or file data
};

#endif // HTTP_REQUEST_TASK_H
