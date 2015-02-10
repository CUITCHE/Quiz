#include "stdafx.h"
#include "NetworkControl.h"
#include "packets.h"
#include <QTcpSocket>
#include <QJsonDocument>
#include <QFile>
#include <QHostAddress>
#include <memory>
using namespace std;
NetworkControl::NetworkControl(QObject * parent)
	:QObject(parent)
	, m_socket(new QTcpSocket(this))
{
	connect(m_socket, &QTcpSocket::readyRead, this, &NetworkControl::readPendingDatagrams);
	QFile file("setting.json");
	if (!file.open(QIODevice::ReadOnly)){
		QMessageBox::information(nullptr, "提示", "seeting.json配置文件出错！",QMessageBox::Yes);
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

NetworkControl::~NetworkControl()
{
	delete m_socket;
}

void NetworkControl::readPendingDatagrams()
{
	QByteArray data = m_socket->readAll();
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(data, &error);
	if (error.error != QJsonParseError::NoError){
		qDebug() << "json parse error! " << error.errorString();
		return;
	}
	if (jsonDocument.isObject() == false){
		return;
	}
	auto res = jsonDocument.toVariant();
	auto result = res.toMap();
	int select = result["action"].toInt();
	switch (select)
	{
	case NetAction::Login:
		LoginFromServer(data);
		break;
	case NetAction::TestRequest:
		TestRequestFromServer(data);
		break;
	case NetAction::Commit:
		break;
	case NetAction::Confirmation:
		ConfirmationFromServer(data);
		break;
	default:
		break;
	}
}

void NetworkControl::send(Packet *packet)
{
	auto res = packet->parse();
	QByteArray array = QJsonDocument::fromVariant(res).toJson();

	auto sendNum = m_socket->write(array);
	if (sendNum != array.size()){
		qDebug() << m_socket->errorString();
	}
}

void NetworkControl::reconnect()
{
	while (m_socket->state() == QAbstractSocket::UnconnectedState){
		qDebug() << "正在重连……";
		m_socket->abort();
		m_socket->connectToHost(QHostAddress(ip), port);
		if (m_socket->waitForConnected(10 * 1000)){
			break;
		}
	}
}

void NetworkControl::Login(const QString &name, const QString &logincode)
{
	LoginPacket *packet(new LoginPacket);
	packet->setName(name);
	packet->setLoginCode(logincode);
	this->send(packet);
	delete packet;
}

void NetworkControl::TestRequest()
{
	TestRequestPacket *packet(new TestRequestPacket);
	this->send(packet);
	delete packet;
}

void NetworkControl::Commit(const int userId, const int subject, const QString &text)
{
	CommitPacket *packet(new CommitPacket);
	packet->setUserId(userId);
	packet->setSubjectNum(subject);
	packet->setText(text);
	this->send(packet);
	delete packet;
}

void NetworkControl::LoginFromServer(const QVariant &data)
{
	unique_ptr<LoginPacket> pakcet(new LoginPacket);
	pakcet->parse(data);
	int userId = pakcet->getUserId();
}

void NetworkControl::TestRequestFromServer(const QVariant &data)
{
	unique_ptr<TestRequestPacket> packet(new TestRequestPacket);
	packet->parse(data);
	auto title = packet->getTitle();
	auto chapters = packet->getChapter().toVariantList();
	auto subjects = packet->getSubject().toVariantList();
}

void NetworkControl::ConfirmationFromServer(const QVariant &data)
{
	unique_ptr<ConfirmationPacket> packet(new ConfirmationPacket);
	packet->parse(data);
	int whichAction = packet->getWhichAction();
	int other = packet->getOther();
	switch (whichAction)
	{
	case NetAction::Login:
		
		break;
	case NetAction::TestRequest:
		
		break;
	case NetAction::Commit:
		break;
	case NetAction::Confirmation:
		
		break;
	default:
		break;
	}
}
