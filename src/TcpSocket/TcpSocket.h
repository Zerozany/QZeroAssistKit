_Pragma("once");
#include <QTcpSocket>

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

class QZERO_API TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit(true) TcpSocket(QObject* _parent = nullptr);

    virtual ~TcpSocket() noexcept = default;

private:
    auto connectSignal2Slot() noexcept -> void;

protected Q_SLOTS:
    virtual auto onReadyRead() -> void;

    virtual auto onBytesWritten(quint64 _bytes) -> void;

    virtual auto onConnected() -> void;

    virtual auto onDisconnected() -> void;
};
