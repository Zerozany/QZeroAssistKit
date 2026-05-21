#include "ClassMate.h"
#include <QDateTime>
#include <QJsonDocument>

ClassMate::ClassMate(QObject* _parent) : QObject{_parent}
{
    std::invoke(&ClassMate::initBasicInfo, this);
}

auto ClassMate::initBasicInfo() noexcept -> void
{
    QDateTime currentTime{QDateTime::currentDateTime()};
    this->setClassID(currentTime.toString("yyyyMMddHHmmss"));
    this->setCreatTime(currentTime.toString("yyyy-MM-dd HH:mm:ss"));
}

QString ClassMate::classID() const
{
    return m_classID;
}

void ClassMate::setClassID(const QString& _classID)
{
    if (m_classID == _classID)
    {
        return;
    }
    m_classID = _classID;
    Q_EMIT this->classIDChanged();
}

QString ClassMate::creatTime() const
{
    return m_creatTime;
}

void ClassMate::setCreatTime(const QString& _creatTime)
{
    if (m_creatTime == _creatTime)
    {
        return;
    }
    m_creatTime = _creatTime;
    Q_EMIT this->creatTimeChanged();
}

QString ClassMate::endTime() const
{
    return m_endTime;
}

void ClassMate::setEndTime(const QString& _endTime)
{
    if (m_endTime == _endTime)
    {
        return;
    }
    m_endTime = _endTime;
    Q_EMIT this->endTimeChanged();
}

auto ClassMate::toJson() const noexcept -> QJsonObject
{
    QJsonObject jsonObject{};
    jsonObject["classID"]   = this->classID();
    jsonObject["creatTime"] = this->creatTime();
    jsonObject["endTime"]   = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    return jsonObject;
}

auto ClassMate::fromJson(const QJsonObject& _jsonObject) -> void
{
    this->setClassID(_jsonObject.value("classID").toString());
    this->setCreatTime(_jsonObject.value("creatTime").toString());
    this->setEndTime(_jsonObject.value("endTime").toString());
}

QTextStream& operator<<(QTextStream& _inputStream, const ClassMate& _classMate)
{
    QJsonDocument jsonDocument{_classMate.toJson()};
    _inputStream << jsonDocument.toJson(QJsonDocument::Indented);
    return _inputStream;
}

QTextStream& operator>>(QTextStream& _outputStream, ClassMate& _classMate)
{
    QString       jsonStr{_outputStream.readAll()};
    QJsonDocument jsonDocument{QJsonDocument::fromJson(jsonStr.toUtf8())};
    if (jsonDocument.isObject())
    {
        _classMate.fromJson(jsonDocument.object());
    }
    return _outputStream;
}
