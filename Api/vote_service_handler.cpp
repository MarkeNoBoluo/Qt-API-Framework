#include "vote_service_handler.h"
#include <QJsonObject>
#include "Logger.h"
VoteServiceHandler::VoteServiceHandler()
{

}

void VoteServiceHandler::handleSuccess(const QJsonDocument &doc)
{
    QJsonObject obj = doc.object();
    LogInfo << "response code:"<<obj["code"].toInt();
    LogInfo << "response msg:"<<obj["msg"].toString();
}

void VoteServiceHandler::handleError(const QString &error)
{
    LogErr << "response error:"<<error;
}

void VoteServiceHandler::handleProgress(int progress)
{
    LogInfo << "response progress:"<<progress;
}
