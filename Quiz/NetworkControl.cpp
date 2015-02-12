#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "packets.h"
#include "NetworkControl.h"

#include <QTcpSocket>
#include <QJsonDocument>
#include <QFile>
#include <QHostAddress>
#include <memory>
using namespace std;
NetworkControl::NetworkControl(QObject * parent)
	:QObject(parent)
	, m_socket(nullptr)
{
	getIpAndPortFromLocalJsonFile();
	
}

NetworkControl::~NetworkControl()
{
	delete m_socket;
}

void NetworkControl::readPendingDatagrams()
{
	QByteArray data = m_socket->readAll();
	g_terminalControl->parsePacketFromByte(data);
}

void NetworkControl::send(Packet *packet)
{
	if (this->reconnect() == false){
		return;
	}
	auto res = packet->parse();
	QByteArray array = QJsonDocument::fromVariant(res).toJson();

	auto sendNum = m_socket->write(array);
	if (sendNum != array.size()){
		qDebug() << m_socket->errorString();
	}
}

bool NetworkControl::reconnect()
{
	if (m_socket==nullptr||m_socket->state() == QAbstractSocket::UnconnectedState){
		g_terminalControl->startReconnectThread();
		return false;
	}
	return true;
}

void NetworkControl::getIpAndPortFromLocalJsonFile()
{
	QFile file("setting.json");
	if (!file.open(QIODevice::ReadOnly)){
		QMessageBox::information(nullptr, "提示", "seeting.json配置文件出错！", QMessageBox::Yes);
		exit(0);
	}
	QByteArray data = file.readAll();
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &error);
	if (error.error != QJsonParseError::NoError){
		QMessageBox::information(nullptr, "提示", "json文件parse错误", QMessageBox::Yes);
		exit(0);
	}
	auto ret = jsonDocument.toVariant().toMap();
	ip = ret["ip"].toString();
	port = ret["port"].toInt();
}