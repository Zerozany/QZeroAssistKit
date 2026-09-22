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

void TcpSocket::onReadyRead()
{
}

void TcpSocket::onBytesWritten(quint64 _bytes)
{
}

void TcpSocket::onConnected()
{
}

void TcpSocket::onDisconnected()
{
}
