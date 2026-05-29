_Pragma("once");
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef QZeroAssistKit
        #define QZERO_API Q_DECL_EXPORT
    #else
        #define QZERO_API Q_DECL_IMPORT
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define QZERO_API __attribute__((visibility("default")))
#else
    #define QZERO_API
#endif

class QZERO_API SqlManager : public QObject
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
    QSqlQuery query{};
    do
    {
        if (!m_databasesList.contains(_dataBaseName))
        {
            qWarning() << "Database not found:" << _dataBaseName;
            break;
        }
        QSqlDatabase dataBase{m_databasesList.value(_dataBaseName)};
        query = QSqlQuery{dataBase};
        if (!dataBase.isOpen() && !dataBase.open())
        {
            qWarning() << "Cannot open database:" << _dataBaseName;
            break;
        }
        if (!query.exec(_sqlCode))
        {
            qWarning() << "Execute sqlCode failed:" << _sqlCode;
            break;
        }
    } while (false);
    if constexpr (std::is_same_v<ReturnType, QSqlQuery>)
    {
        return query;
    }
}
