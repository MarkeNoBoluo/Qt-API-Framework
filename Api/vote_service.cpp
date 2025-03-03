#include "vote_service.h"

VoteService::VoteService(QObject* parent) : ApiServiceBase(parent) {

}

void VoteService::updateAllVoteItem(const QMap<QString, QString>& params) {
    Http_Request_Task task(Http_Request_Task::GET, "/api/client/voting/findAllVotingItem", params);
    sendApiRequest(API_UPDATE_ALL_VOTE_ITEM_GET,task);

}

void VoteService::createNewVoteItem(const QByteArray& data) {
//    Http_Request_Task task(Http_Request_Task::POST, "/api/vote/create", data);
}

void VoteService::modifyExistVoteItem(const QByteArray& data) {
//    Http_Request_Task task(Http_Request_Task::POST, "/api/vote/modify", data);
}

void VoteService::removeMultiVoteItem(const QByteArray& data) {
//    Http_Request_Task task(Http_Request_Task::POST, "/api/vote/removeMulti", data);
}

void VoteService::countResultVoteItem(const QMap<QString, QString>& params) {
    Http_Request_Task task(Http_Request_Task::GET, "/api/vote/countResult", params,QByteArray());
    sendApiRequest(API_COUNT_RESULT_VOTE_ITEM_GET,task);
}

void VoteService::controlExistVoteItem(const QByteArray& data) {
//    Http_Request_Task task(Http_Request_Task::POST, "/api/vote/control", data);
    //    sendRequest(task);
}

