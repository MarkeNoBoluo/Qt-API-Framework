#include <QCoreApplication>
#include "http_request_manager.h"
#include "vote_service.h"
#include "vote_service_handler.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Http_Request_Manager::getInstance()->setServerAddress("meeting.soundking.com.cn");//设置服务器地址
//    Http_Request_Manager::getInstance()->setServerAddress("192.168.42.101");//设置服务器地址
    VoteServiceHandler h;
    VoteService v;
    v.setResponseHandler(&h);
    v.updateAllVoteItem({{"attendUser","5642a739-85bf-4582-b3e1-5c0f6dc01329"},{"conferenceGuid","76050537-f63e-41db-a060-949d9d9def52"}
                         ,{"pageNum","1"},{"pageSize","100"}});

    return a.exec();
}
