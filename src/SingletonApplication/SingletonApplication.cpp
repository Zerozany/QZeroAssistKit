#include "SingletonApplication.h"

SingletonApplication::SingletonApplication(const QString& _processID, QObject* _parent) : QObject{_parent}, m_processID{_processID}
{
}

auto SingletonApplication::instance(const QString& _processID, QObject* _parent) noexcept -> SingletonApplication*
{
    static SingletonApplication singletonApplication{_processID, _parent};
    return &singletonApplication;
}

auto SingletonApplication::init() noexcept -> void
{
    m_shareMemory.setKey(m_processID);
    if (!m_shareMemory.create(1, QSharedMemory::ReadWrite))
    {
        qFatal("%s", tr("当前应用已在系统中运行").toUtf8().constData());
    }
}
