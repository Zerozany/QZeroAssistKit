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

    explicit(true) TcpSocket(const QString& _host, quint16 _port, QObject* _parent = nullptr);

    virtual ~TcpSocket() noexcept = default;

protected:
    QString m_host{};
    quint16 m_port{};
};
