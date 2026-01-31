#include "SingletonApplication.h"

static constexpr const char* SingletonApplicationKey{"SingletonApplicationKey"};

SingletonApplication::SingletonApplication(QObject* _parent) : QObject{_parent}
{
}

auto SingletonApplication::instance(QObject* _parent) noexcept -> SingletonApplication*
{
    static SingletonApplication singletonApplication{_parent};
    return &singletonApplication;
}

auto SingletonApplication::init() noexcept -> void
{
    m_shareMemory.setKey(SingletonApplicationKey);
    if (!m_shareMemory.create(strlen(SingletonApplicationKey), QSharedMemory::ReadOnly))
    {
        std::exit(EXIT_FAILURE);
    }
}
