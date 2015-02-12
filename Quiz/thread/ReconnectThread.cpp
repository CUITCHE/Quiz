#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "ReconnectThread.h"
#include "NetworkControl.h"
#include <QTcpSocket>
#include <QHostAddress>
ReconnectThread::ReconnectThread(QTcpSocket **sock, NetworkControl *parent)
	:QThread(parent)
	, m_socket(sock)
	, data(parent)
{

}

void ReconnectThread::run()
{
	static QTcpSocket *sock = nullptr;
	if (*m_socket == nullptr){
		sock = new QTcpSocket;
	}
	if (sock->state() == QAbstractSocket::UnconnectedState){
		emit information(tr("网络连接断开，正在重连"));
	}
	while (sock->state() == QAbstractSocket::UnconnectedState){
		sock->abort();
		sock->connectToHost(QHostAddress(data->ip), data->port);
		if (sock->waitForConnected(10 * 1000)){
			break;
		}
		msleep(100);
	}
	*m_socket = sock;
	connect(sock, &QTcpSocket::readyRead, data, &NetworkControl::readPendingDatagrams);
	emit information(tr("网络已恢复，请重试"));
}

