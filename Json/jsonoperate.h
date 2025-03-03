#ifndef JSONOPERATE_H
#define JSONOPERATE_H

/**
*类名： JsonOperate
*编写： wddkxg@look.com
*设计： Json文件操作类
*功能：
*
*/

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonParseError>
#include <QDebug>

class JsonOperate
{
public:
    JsonOperate(const QString& fileName);//构造函数，接受JSON文件名

    QJsonObject GetJsonObject();

    bool ReadFile();//从文件中读取JSON对象

    bool WriteFile(QJsonObject jsonObj);//将JSON对象写入文件中

    // 添加、获取、删除操作
    void AddItem(const QString &key, const QVariant &value); // 添加JSON对象的键值对

    QVariant GetItem(const QString &key) const; // 获取JSON对象的键值

    bool RemoveItem(const QString &key); // 删除JSON对象的键值


private:
    QString m_fileName;         //JSON文件名
    QJsonObject m_jsonObject;   //JSON对象名
};

#endif // JSONOPERATE_H
