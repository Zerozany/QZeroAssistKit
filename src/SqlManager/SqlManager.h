_Pragma("once");
#include <QObject>

class SqlManager
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) -> SqlManager*;

    ~SqlManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(SqlManager)

protected:
    explicit(true) SqlManager(QObject* _parent = nullptr);
};
