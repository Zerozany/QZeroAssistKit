_Pragma("once");
#include <QObject>
#include <QSharedMemory>

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

class QZERO_API SingletonApplication : public QObject
{
    Q_OBJECT
public:
    ~SingletonApplication() noexcept = default;

public:
    static auto instance(QObject* _parent = nullptr) noexcept -> SingletonApplication*;

    auto init() noexcept -> void;

private:
    explicit(true) SingletonApplication(QObject* _parent = nullptr);

private:
    QSharedMemory m_shareMemory{};
};
