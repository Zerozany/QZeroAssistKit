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
}

auto TcpSocket::onReadyRead() -> void
{
}

auto TcpSocket::onBytesWritten(quint64 _bytes) -> void
{
}

auto TcpSocket::onConnected() -> void
{
}

auto TcpSocket::onDisconnected() -> void
{
}
