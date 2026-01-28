_Pragma("once");
#include <QObject>
#include <QVariantMap>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef QZeroAssistKit
        #define QZERO_API Q_DECL_EXPORT
    #else
        #define QZERO_API Q_DECL_IMPORT
    #endif
#else
    #define QZERO_API
#endif

class QZERO_API ApplicationConfig : public QObject
{
    Q_OBJECT
public:
    ~ApplicationConfig() noexcept = default;

public:
    inline static auto instance() noexcept -> ApplicationConfig*;

    auto init(const QString& _quickStyle = QString{}, const QVector<Qt::ApplicationAttribute>& _attributeVector = QVector<Qt::ApplicationAttribute>{}, const QVariantMap& _envVariantMap = QVariantMap{}) noexcept -> void;

private:
    explicit(true) ApplicationConfig(QObject* _parent = nullptr);

    auto initAppStyle(const QString& _quickStyle = QString{}) noexcept -> void;

    auto initAppAttribute(const QVector<Qt::ApplicationAttribute>& _attributeVector = QVector<Qt::ApplicationAttribute>{}) noexcept -> void;

    auto initAppEnv(const QVariantMap& _envVariantMap = QVariantMap{}) noexcept -> void;
};
