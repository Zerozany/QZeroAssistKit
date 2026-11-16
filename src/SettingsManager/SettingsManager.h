_Pragma("once");
#include <QSettings>

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

class ASSISTKIT_DLL SettingsManager : public QSettings
{
    Q_OBJECT
public:
    explicit(true) SettingsManager(const QString& _fileName, Format _format, QObject* _parent = nullptr);

    virtual ~SettingsManager() noexcept = default;

public:
    virtual void init();
};
