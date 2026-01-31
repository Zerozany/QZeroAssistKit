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

class QZERO_API ApplicationConfigBase : public QObject
{
    Q_OBJECT
public:
    explicit(true) ApplicationConfigBase(QObject* _parent = nullptr);
    ~ApplicationConfigBase() noexcept = default;

protected:
    virtual auto initAppStyle() noexcept -> void = 0;

    virtual auto initAppAttribute() noexcept -> void = 0;

    virtual auto initAppEnv() noexcept -> void = 0;
};
