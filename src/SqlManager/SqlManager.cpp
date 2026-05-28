#include "SqlManager.h"

auto SqlManager::instance(QObject* _parent) -> SqlManager*
{
    static SqlManager* sqlManager{new SqlManager{_parent}};
    return sqlManager;
}

SqlManager::SqlManager(QObject* _parent)
{
}
