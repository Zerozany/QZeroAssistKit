_Pragma("once");
#include <QObject>

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

struct ApplicationStyle
{
    QString WindowStyle{};
    QString UnixStyle{};
    QString AndroidStyle{};
    QString MacStyle{};
    QString IosStyle{};
};

class QZERO_API ApplicationConfigBase : public QObject
{
    Q_OBJECT
public:
    explicit(true) ApplicationConfigBase(QObject* _parent = nullptr);
    ~ApplicationConfigBase() noexcept = default;

public:
    virtual auto initAppStyle(const ApplicationStyle& _applicationStyle) noexcept -> void;

    virtual auto initAppAttribute(const QMap<Qt::ApplicationAttribute, bool>& _attributeMap) noexcept -> void;

    virtual auto initAppEnv(const QMap<const char*, QByteArrayView>& _envMap) noexcept -> void;
};
