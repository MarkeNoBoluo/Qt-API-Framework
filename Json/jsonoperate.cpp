#include "jsonoperate.h"
#include "Logger.h"

JsonOperate::JsonOperate(const QString &fileName):m_fileName(fileName)
{
}

QJsonObject JsonOperate::GetJsonObject()
{
    return m_jsonObject;//返回当前JSON对象
}

bool JsonOperate::ReadFile()
{
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        LogErr <<  "Failed to open json file for reading!";
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);//获取JSON文档对象
    if (jsonError.error != QJsonParseError::NoError) {
         LogErr << "Failed to parse JSON:" << jsonError.errorString();
        return false;
    }

    m_jsonObject = jsonDoc.object();
    return true;
}

bool JsonOperate::WriteFile(QJsonObject jsonObj)
{
    m_jsonObject = jsonObj;
    QFile file(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QJsonDocument jsonDoc(m_jsonObject);
    file.write(jsonDoc.toJson());//写入JSON格式数据
    file.close();

    return true;
}

void JsonOperate::AddItem(const QString &key, const QVariant &value)
{
    m_jsonObject[key] = QJsonValue::fromVariant(value);
}

QVariant JsonOperate::GetItem(const QString &key) const
{
    if (m_jsonObject.contains(key)) {
        return m_jsonObject.value(key).toVariant();
    } else {
        LogErr <<  "Key not found:" << key;
        return QVariant();
    }
}

bool JsonOperate::RemoveItem(const QString &key)
{
    if (m_jsonObject.contains(key)) {
        m_jsonObject.remove(key);
        return true;
    } else {
        LogErr << "Key not found:" << key;
        return false;
    }
}
