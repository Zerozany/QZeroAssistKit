#include "TcpSocket.h"

TcpSocket::TcpSocket(QObject* _parent) : QTcpSocket{_parent}
{
    std::invoke(&TcpSocket::connectSignal2Slot, this);
}

auto TcpSocket::connectSignal2Slot() noexcept -> void
{
    connect(this, &QTcpSocket::readyRead, this, &TcpSocket::onReadyRead);
    connect(this, &QTcpSocket::bytesWritten, this, &TcpSocket::onBytesWritten);
    connect(this, &QTcpSocket::connected, this, &TcpSocket::onConnected);
    connect(this, &QTcpSocket::disconnected, this, &TcpSocket::onDisconnected);
    connect(this, &QTcpSocket::errorOccurred, this, &TcpSocket::onErrorOccurred);
}

void TcpSocket::onReadyRead()
{
}

void TcpSocket::onBytesWritten(quint64 _bytes)
{
    Q_UNUSED(_bytes)
}

void TcpSocket::onConnected()
{
}

void TcpSocket::onDisconnected()
{
}

void TcpSocket::onErrorOccurred(const TcpSocket::SocketError& _error)
{
    Q_UNUSED(_error)
}
