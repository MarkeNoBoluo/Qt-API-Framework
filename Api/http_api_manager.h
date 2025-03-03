#ifndef Http_Api_Manager_H
#define Http_Api_Manager_H

#include <QObject>
#include <memory>
#include <QJsonValue>
#include "http_request_manager.h"


enum ApiType {//枚举API请求
    /*投票相关 -- 秘书端*/
    API_UPDATE_ALL_VOTE_ITEM_GET    ,
    API_CREATE_NEW_VOTE_ITEM_POST   ,
    API_MODIFY_EXIST_VOTE_ITEM_POST ,
    API_REMOVE_MULTI_VOTE_ITEM_POST ,
    API_COUNT_RESULT_VOTE_ITEM_GET  ,
    API_CONTROL_EXIST_VOTE_ITEM_POST,

    /*投票相关 -- 参会人端*/
    API_UPDATE_RUNING_VOTE_ITEM_GET ,
    API_SUBMIT_RUNING_VOTE_ITEM_POST,

    /*会标相关 -- 秘书端*/
    API_CREATE_NEW_LOGO_ITEM_POST  ,
    API_UPDATE_ALL_LOGO_ITEM_GET   ,
    API_UPDATE_SINGLE_LOGO_ITEM_GET,
    API_MODIFY_EXIST_LOGO_ITEM_POST,
    API_REMOVE_MULTI_LOGO_ITEM_POST,

    /*批注相关 -- 秘书端*/
    API_CREATE_NEW_ANNOTA_ITEM_POST  ,
    API_UPDATE_ALL_ANNOTA_ITEM_GET   ,
    API_MODIFY_EXIST_ANNOTA_ITEM_POST,
    API_REMOVE_MULTI_ANNOTA_ITEM_POST,

    /*议程相关 -- 秘书端*/
    API_CREATE_NEW_AGENDA_ITEM_POST  ,
    API_UPDATE_ALL_AGENDA_ITEM_GET   ,
    API_MODIFY_EXIST_AGENDA_ITEM_POST,
    API_REMOVE_MULTI_AGENDA_ITEM_POST,

    /*同屏相关 -- 秘书端*/
    API_CREATE_NEW_GROUP_ITEM_POST   ,
    API_UPDATE_ALL_GROUP_ITEM_GET    ,
    API_UPDATE_SINGLE_GROUP_ITEM_GET ,
    API_JOIN_EXIST_GROUP_ITEM_POST   ,
    API_MODIFY_EXIST_GROUP_ITEM_POST ,
    API_QUIT_EXIST_GROUP_ITEM_POST   ,
    API_REMOVE_SINGLE_GROUP_ITEM_POST,
    API_REMOVE_MULTI_GROUP_ITEM_POST ,

    /*投影相关*/
    API_START_NEW_PROJECTION_OR_LOGO_POST,
    API_PERMISSION_PROJECTION_GET        ,

    /*设备相关 -- 秘书端*/
    API_UPDATE_ALL_DEVICE_BY_ROOM_GET,
    API_CONTROL_SINGLE_DEVICE_POST   ,

    /*呼叫服务相关*/
    API_CREATE_NEW_CALLSERVICE_POST,

    /*会议室相关*/
    API_UPDATE_ALL_ROOM_GET,

    /*会议相关*/
    API_UPDATE_DETAIL_CONFERENCE_POST,

    /*坐席相关*/
    API_UPDATE_SEATINGLIST_BY_CONFERENCE_GET,
    API_UPDATE_SEATINGLIST_CANVASINFO_GET   ,

    /*中控相关 -- 秘书端*/
    API_UPDATE_IOT_ADRESS_BY_ADMIN_GET,

    /*会议资料相关*/
    API_UPDATE_ALL_METERIAL_BY_AGENDA_AND_TYPE_GET,
    API_CREATE_SINGLE_MATERIAL_POST               ,
    API_REMOVE_SINGLE_MATERIAL_POST               ,

    /*签到相关*/
    API_UPDATE_ALL_SIGNED_BY_CONFERENCE_GET,
    API_COUNT_ALL_SIGNED_BY_CONFERENCE_GET ,

    /*参会人相关*/
    API_UPDATE_ALL_USER_ITEM_BY_CONFERENCE_GET,
    API_UPDATE_NO_BIND_USER_ITEM_GET          ,
    API_UPDATE_SINGLE_SIGNED_SATTE_POST       ,
    API_UPDATE_SINGLE_LOGIN_STATE_POST        ,

    /*视频相关*/
    API_UPDATE_ALL_VIDEO_ITEM_GET,

    /*菜单相关*/
    API_UPDATE_MENU_BY_ROOM_GET
};

class Http_Api_Manager : public QObject {
    Q_OBJECT
public:
    static Http_Api_Manager* getInstance(QObject* parent = nullptr); // 单例访问
    ~Http_Api_Manager();

    /// 发送请求并指定接收对象和槽函数
    void requestApiData(ApiType apiType, const Http_Request_Task& task,
                        QObject* receiver,
                        std::function<void(const QJsonDocument&)> successCallback,
                        std::function<void(const QString&)> errorCallback = nullptr,
                        std::function<void(int)> progressCallback = nullptr);

private:
    Http_Api_Manager(QObject* parent = nullptr);
    static Http_Api_Manager* m_gInstance; // 单例实例

    // 构造 API URL
    QString constructApiUrl(ApiType type) const;

    // 处理响应
    void processNormalResponse(const QByteArray& response,
                               std::function<void(const QJsonDocument&)> callbackHandle);
    void processErrorResponse(const QByteArray& response,
                              std::function<void(const QString&)> callbackHandle);

    // 前向声明 Private 类
    class Private;
    std::unique_ptr<Private> d;         // 私有实现指针
};
#endif // Http_Api_Manager_H
