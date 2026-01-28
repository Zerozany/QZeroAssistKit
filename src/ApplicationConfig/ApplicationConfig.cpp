#include "ApplicationConfig.h"
#include <QQuickStyle>
#include <QGuiApplication>

auto ApplicationConfig::instance() noexcept -> ApplicationConfig*
{
    static ApplicationConfig systemConfig{};
    return &systemConfig;
}

auto ApplicationConfig::init(const QString& _quickStyle, const QVector<Qt::ApplicationAttribute>& _attributeVector, const QVariantMap& _envVariantMap) noexcept -> void
{
    std::invoke(&ApplicationConfig::initAppStyle, this, _quickStyle);
    std::invoke(&ApplicationConfig::initAppAttribute, this, _attributeVector);
    std::invoke(&ApplicationConfig::initAppEnv, this, _envVariantMap);
}

ApplicationConfig::ApplicationConfig(QObject* _parent) : QObject{_parent}
{
}

auto ApplicationConfig::initAppStyle(const QString& _quickStyle) noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle(_quickStyle);
#elif defined(Q_OS_WINDOWS)
    QQuickStyle::setStyle(_quickStyle);
#endif
}

auto ApplicationConfig::initAppAttribute(const QVector<Qt::ApplicationAttribute>& _attributeVector) noexcept -> void
{
    for (const auto& _attribute : _attributeVector)
    {
        QGuiApplication::setAttribute(_attribute);
    }
}

auto ApplicationConfig::initAppEnv(const QVariantMap& _envVariantMap) noexcept -> void
{
    for (const auto& [_key, _value] : _envVariantMap.toStdMap())
    {
        qputenv(_key.toUtf8(), _value.toByteArray().constData());
    }
}
