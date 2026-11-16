_Pragma("once");
#include <QObject>

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

struct SoftwareStyle
{
    QString WindowsStyle{};
    QString UnixStyle{};
    QString AndroidStyle{};
    QString MacStyle{};
    QString IosStyle{};
};

class ASSISTKIT_DLL SoftwareManager : public QObject
{
    Q_OBJECT
public:
    static auto instance() noexcept -> SoftwareManager*;

    ~SoftwareManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(SoftwareManager)
protected:
    explicit(true) SoftwareManager(QObject* _parent = nullptr);

protected:
    virtual auto setSoftwareStyle(const SoftwareStyle& _softwareStyle) noexcept -> void;

    virtual auto setSoftwareAttribute(const QMap<Qt::ApplicationAttribute, bool>& _attributeMap) noexcept -> void;

    virtual auto setSoftwareEnv(const QMap<const char*, QByteArrayView>& _envMap) noexcept -> void;
};
