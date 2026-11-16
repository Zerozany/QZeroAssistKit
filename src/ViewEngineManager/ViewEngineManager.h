_Pragma("once");
#include <QObject>
#include <QQmlApplicationEngine>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef QZEROASSISTKIT_BUILDING
        #define ASSISTKIT_DLL Q_DECL_EXPORT
    #else
        #define ASSISTKIT_DLL Q_DECL_IMPORT
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define ASSISTKIT_DLL __attribute__((visibility("default")))
#else
    #define ASSISTKIT_DLL
#endif

class ASSISTKIT_DLL ViewEngineManager : public QObject
{
    Q_OBJECT
public:
    explicit(true) ViewEngineManager(QQmlApplicationEngine& _qmlApplicationEngine, QObject* _parent = nullptr);

    ~ViewEngineManager() noexcept = default;

protected:
    virtual auto connectSignal2Slot() noexcept -> void;

    virtual auto loadModule() noexcept -> void = 0;

protected:
    QQmlApplicationEngine& m_qmlApplicationEngine;
};
