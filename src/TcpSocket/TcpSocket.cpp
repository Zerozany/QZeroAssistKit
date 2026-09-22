#include "TcpSocket.h"

TcpSocket::TcpSocket(QObject* _parent) : QTcpSocket{_parent}
{
}

TcpSocket::TcpSocket(const QString& _host, quint16 _port, QObject* _parent) : QTcpSocket{_parent}, m_host{_host}, m_port{_port}
{
}
