#ifndef VOTE_SERVICE_H
#define VOTE_SERVICE_H

#include "api_service_base.h"

class VoteService : public ApiServiceBase  {
    Q_OBJECT
public:
    explicit VoteService(QObject* parent = nullptr);

    // 投票相关的 API 请求方法
    void updateAllVoteItem(const QMap<QString, QString>& params);
    void createNewVoteItem(const QByteArray& data);
    void modifyExistVoteItem(const QByteArray& data);
    void removeMultiVoteItem(const QByteArray& data);
    void countResultVoteItem(const QMap<QString, QString>& params);
    void controlExistVoteItem(const QByteArray& data);

};
#endif // VOTE_SERVICE_H
