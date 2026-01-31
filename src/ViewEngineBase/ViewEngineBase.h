_Pragma("once");
#include <QObject>
#include <QQmlApplicationEngine>

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

class QZERO_API ViewEngineBase : public QObject
{
    Q_OBJECT
public:
    explicit(true) ViewEngineBase(QQmlApplicationEngine& _qmlApplicationEngine, QObject* _parent = nullptr);
    ~ViewEngineBase() noexcept = default;

protected:
    virtual auto connectSignal2Slot() noexcept -> void;

    virtual auto engineLaod() noexcept -> void = 0;

protected:
    QQmlApplicationEngine& m_qmlApplicationEngine [[indeterminate]];
};
