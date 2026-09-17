_Pragma("once");
#include <QSettings>

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

class QZERO_API ConfigSetting : public QSettings
{
    Q_OBJECT
public:
    explicit(true) ConfigSetting(const QString& _fileName, Format _format, QObject* _parent = nullptr);

    virtual ~ConfigSetting() noexcept = default;

protected:
    virtual void loadProperties();
};
