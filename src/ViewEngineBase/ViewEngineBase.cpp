#include "ViewEngineBase.h"
#include <QGuiApplication>

ViewEngineBase::ViewEngineBase(QQmlApplicationEngine& _qmlApplicationEngine, QObject* _parent) : QObject{_parent}, m_qmlApplicationEngine{_qmlApplicationEngine}
{
    std::invoke(&ViewEngineBase::connectSignal2Slot, this);
}

auto ViewEngineBase::connectSignal2Slot() noexcept -> void
{
    connect(&m_qmlApplicationEngine, &QQmlApplicationEngine::objectCreationFailed, qApp, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    connect(&m_qmlApplicationEngine, &QQmlApplicationEngine::warnings, qApp, [](const QList<QQmlError>& _warnings) {   for (const auto &warning : _warnings) {
        qDebug() << warning.toString();
    } }, Qt::QueuedConnection);
}
