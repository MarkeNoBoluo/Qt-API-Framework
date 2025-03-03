#ifndef VOTE_SERVICE_HANDLER_H
#define VOTE_SERVICE_HANDLER_H

#include "api_response_handler.h"

class VoteServiceHandler : public ApiResponseHandler
{
public:
    VoteServiceHandler();

protected:
    void handleSuccess(const QJsonDocument& doc) override;
    void handleError(const QString& error) override;
    void handleProgress(int progress) override;
};

#endif // VOTE_SERVICE_HANDLER_H
