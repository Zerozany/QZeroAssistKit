#include "ApplicationConfigBase.h"
#include <QQuickStyle>
#include <QGuiApplication>
#include <QMap>
#include <ranges>

ApplicationConfigBase::ApplicationConfigBase(QObject* _parent) : QObject{_parent}
{
}

auto ApplicationConfigBase::initAppStyle(const ApplicationStyle& _applicationStyle) noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle(_applicationStyle.AndroidStyle);
#elif defined(Q_OS_WINDOWS)
    QQuickStyle::setStyle(_applicationStyle.WindowStyle);
#elif defined(Q_OS_IOS)
    QQuickStyle::setStyle(_applicationStyle.IosStyle);
#elif defined(Q_OS_MACOS)
    QQuickStyle::setStyle(_applicationStyle.MacStyle);
#elif defined(Q_OS_LINUX)
    QQuickStyle::setStyle(_applicationStyle.UnixStyle);
#endif
}

auto ApplicationConfigBase::initAppAttribute(const QMap<Qt::ApplicationAttribute, bool>& _attributeMap) noexcept -> void
{
    for (const auto& [key, value] : _attributeMap.toStdMap())
    {
        qApp->setAttribute(key, value);
    }
}

auto ApplicationConfigBase::initAppEnv(const QMap<const char*, QByteArrayView>& _envMap) noexcept -> void
{
    for (const auto& [key, value] : _envMap.toStdMap())
    {
        qputenv(key, value);
    }
}
