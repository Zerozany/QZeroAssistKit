#include "ClassMate.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QMetaProperty>

ClassMate::ClassMate(QObject* _parent) : QObject{_parent}
{
    std::invoke(&ClassMate::init, this);
}

auto ClassMate::init() noexcept -> void
{
    QDateTime currentTime{QDateTime::currentDateTime()};
    this->setClassID(currentTime.toString("yyyyMMddHHmmss"));
    this->setCreatTime(currentTime.toString("yyyy-MM-dd HH:mm:ss"));
}

auto ClassMate::toJson() const noexcept -> QJsonObject
{
    QJsonObject        jsonObject{};
    const QMetaObject* meta{this->metaObject()};
    for (int i{}; i < meta->propertyCount(); ++i)
    {
        const QMetaProperty prop{meta->property(i)};
        if (!prop.isReadable() || !prop.isStored())
        {
            continue;
        }
        const QVariant value{prop.read(this)};
        if (!value.isValid() || value.userType() == QMetaType::QObjectStar)
        {
            continue;
        }
        jsonObject[QString::fromUtf8(prop.name())] = QJsonValue::fromVariant(value);
    }
    return jsonObject;
}

auto ClassMate::fromJson(const QJsonObject& _jsonObject) -> void
{
    const QMetaObject* meta{this->metaObject()};
    for (int i{}; i < meta->propertyCount(); ++i)
    {
        const QMetaProperty prop{meta->property(i)};
        if (!prop.isWritable() || !prop.isStored())
        {
            continue;
        }
        const QString key{QString::fromUtf8(prop.name())};
        if (!_jsonObject.contains(key))
        {
            continue;
        }
        const QVariant value{_jsonObject.value(key).toVariant()};
        if (!value.isValid())
        {
            continue;
        }
        prop.write(this, value);
    }
}

QTextStream& operator<<(QTextStream& _outputStream, const ClassMate& _classMate)
{
    QJsonDocument jsonDocument{_classMate.toJson()};
    _outputStream << jsonDocument.toJson(QJsonDocument::Indented);
    return _outputStream;
}

QTextStream& operator>>(QTextStream& _inputStream, ClassMate& _classMate)
{
    QString       jsonStr{_inputStream.readAll()};
    QJsonDocument jsonDocument{QJsonDocument::fromJson(jsonStr.toUtf8())};
    if (jsonDocument.isObject())
    {
        _classMate.fromJson(jsonDocument.object());
    }
    return _inputStream;
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
