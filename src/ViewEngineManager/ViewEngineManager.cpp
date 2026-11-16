#include "ViewEngineManager.h"
#include <QGuiApplication>

ViewEngineManager::ViewEngineManager(QQmlApplicationEngine& _qmlApplicationEngine, QObject* _parent) : QObject{_parent}, m_qmlApplicationEngine{_qmlApplicationEngine}
{
    std::invoke(&ViewEngineManager::connectSignal2Slot, this);
}

auto ViewEngineManager::connectSignal2Slot() noexcept -> void
{
    connect(&m_qmlApplicationEngine, &QQmlApplicationEngine::objectCreationFailed, qApp, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    connect(&m_qmlApplicationEngine, &QQmlApplicationEngine::warnings, qApp, [](const QList<QQmlError>& _warnings) {   
        for (const auto &warning : _warnings) {
            qWarning() << warning.toString();
    } }, Qt::QueuedConnection);
}
