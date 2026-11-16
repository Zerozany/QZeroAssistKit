#include "SoftwareManager.h"
#include <QQuickStyle>
#include <QGuiApplication>
#include <QMap>
#include <ranges>

auto SoftwareManager::instance() noexcept -> SoftwareManager*
{
    static SoftwareManager applicationConfigBase{};
    return &applicationConfigBase;
}

SoftwareManager::SoftwareManager(QObject* _parent) : QObject{_parent}
{
}

auto SoftwareManager::setSoftwareStyle(const SoftwareStyle& _softwareStyle) noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle(_softwareStyle.AndroidStyle);
#elif defined(Q_OS_WINDOWS)
    QQuickStyle::setStyle(_softwareStyle.WindowsStyle);
#elif defined(Q_OS_IOS)
    QQuickStyle::setStyle(_softwareStyle.IosStyle);
#elif defined(Q_OS_MACOS)
    QQuickStyle::setStyle(_softwareStyle.MacStyle);
#elif defined(Q_OS_LINUX)
    QQuickStyle::setStyle(_softwareStyle.UnixStyle);
#endif
}

auto SoftwareManager::setSoftwareAttribute(const QMap<Qt::ApplicationAttribute, bool>& _attributeMap) noexcept -> void
{
    for (const auto& [key, value] : _attributeMap.toStdMap())
    {
        qApp->setAttribute(key, value);
    }
}

auto SoftwareManager::setSoftwareEnv(const QMap<const char*, QByteArrayView>& _envMap) noexcept -> void
{
    for (const auto& [key, value] : _envMap.toStdMap())
    {
        qputenv(key, value);
    }
}
