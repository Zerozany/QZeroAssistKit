_Pragma("once");
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class SqlManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString dataBaseName READ dataBaseName WRITE setDatabaseName NOTIFY databaseNameChanged)
public:
    static auto instance(QObject* _parent = nullptr) -> SqlManager*;

    ~SqlManager() noexcept;

    Q_DISABLE_COPY_MOVE(SqlManager)
public:
    QString dataBaseName() const;
    void    setDatabaseName(const QString& _dataBaseName);

public:
    template <typename ReturnType>
    auto executeSql(const QString& _dataBaseName, const QString& _sqlCode) -> ReturnType;

private:
    auto connectSignal2Slot() -> void;

protected:
    explicit(true) SqlManager(QObject* _parent = nullptr);

Q_SIGNALS:
    void databaseNameChanged();

private Q_SLOTS:
    void onDatabaseNameChanged();

private:
    QMap<QString, QSqlDatabase> m_databasesList{};
    QString                     m_dataBaseName{};
};

template <typename ReturnType>
inline auto SqlManager::executeSql(const QString& _dataBaseName, const QString& _sqlCode) -> ReturnType
{
    if (!m_databasesList.contains(_dataBaseName))
    {
        qWarning() << "Database not found:" << _dataBaseName;
        return ReturnType{};
    }
    QSqlDatabase dataBase{m_databasesList.value(_dataBaseName)};
    if (!dataBase.isOpen() && !dataBase.open())
    {
        qWarning() << "Cannot open database:" << _dataBaseName;
        return ReturnType{};
    }
    QSqlQuery query{dataBase};
    if (!query.exec(_sqlCode))
    {
        qWarning() << "Execute sqlCode failed:" << _sqlCode;
    }
    if constexpr (std::is_void_v<ReturnType>)
    {
        return ReturnType{};
    }
    return query;
}
