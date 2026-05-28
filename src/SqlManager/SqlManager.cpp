#include "SqlManager.h"

constexpr const char* SqlDriverName{"QSQLITE"};

auto SqlManager::instance(QObject* _parent) -> SqlManager*
{
    static SqlManager* sqlManager{new SqlManager{_parent}};
    return sqlManager;
}

SqlManager::~SqlManager() noexcept
{
    for (auto& [_dataBaseName, _dataBase] : m_databasesList.toStdMap())
    {
        if (!_dataBase.isOpen())
        {
            continue;
        }
        _dataBase.close();
        QSqlDatabase::removeDatabase(_dataBaseName);
    }
}

SqlManager::SqlManager(QObject* _parent) : QObject{_parent}
{
    std::invoke(&SqlManager::connectSignal2Slot, this);
}

QString SqlManager::dataBaseName() const
{
    return m_dataBaseName;
}

void SqlManager::setDatabaseName(const QString& _dataBaseName)
{
    if (m_dataBaseName == _dataBaseName)
    {
        return;
    }
    m_dataBaseName = _dataBaseName;
    Q_EMIT this->databaseNameChanged();
}

auto SqlManager::connectSignal2Slot() -> void
{
    connect(this, &SqlManager::databaseNameChanged, this, &SqlManager::onDatabaseNameChanged);
}

void SqlManager::onDatabaseNameChanged()
{
    if (QSqlDatabase::contains(this->dataBaseName()))
    {
        return;
    }
    QSqlDatabase qSqlDatabase{QSqlDatabase::addDatabase(SqlDriverName, this->dataBaseName().chopped(3))};
    qSqlDatabase.setDatabaseName(this->dataBaseName());
    if (!qSqlDatabase.open())
    {
        qWarning() << "Database not open:" << this->dataBaseName();
    }
    m_databasesList.insert(this->dataBaseName(), QSqlDatabase::addDatabase(SqlDriverName, this->dataBaseName().chopped(3)));
}
