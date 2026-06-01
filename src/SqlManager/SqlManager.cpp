#include "SqlManager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QSqlError>
#include <QRegularExpression>

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

QPair<QString, DataBasePathType> SqlManager::dataBaseName() const
{
    return m_dataBaseName;
}

void SqlManager::setDatabaseName(const QPair<QString, DataBasePathType>& _dataBaseName)
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
    QString dataBasePath{this->dataBaseName().first};
    if (this->dataBaseName().second == DataBasePathType::ResourcePath)
    {
#if defined(Q_OS_WINDOWS)
        dataBasePath = qApp->applicationDirPath() + this->dataBaseName().first.remove(QRegularExpression{"^.*:"});
#elif defined(Q_OS_ANDROID)
        dataBasePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + this->dataBaseName().first.remove(QRegularExpression{"^.*:"});
#endif
        if (!QDir{}.mkpath(QFileInfo{dataBasePath}.absolutePath()))
        {
            return;
        }
        if (!QFile::exists(dataBasePath))
        {
            QFile::copy(this->dataBaseName().first, dataBasePath);
        }
    }
    QSqlDatabase qSqlDatabase{QSqlDatabase::addDatabase(SqlDriverName, dataBasePath.left(dataBasePath.lastIndexOf('.')))};
    qSqlDatabase.setDatabaseName(dataBasePath);
    if (!qSqlDatabase.open())
    {
        qWarning() << "Database not open:" << qSqlDatabase.lastError().text();
    }
    if (m_databasesList.contains(dataBasePath.left(dataBasePath.lastIndexOf('.'))))
    {
        return;
    }
    m_databasesList.insert(this->dataBaseName().first, qSqlDatabase);
}
