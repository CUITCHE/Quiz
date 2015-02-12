#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "packets.h"
#include "TerminalControl.h"
#include "LoginWidget.h"
#include "QuizWidget.h"
#include "NetworkControl.h"
#include "thread/ReconnectThread.h"
TerminalControl::TerminalControl(QObject *parent)
	: QObject(parent)
	, networkControl(new NetworkControl(this))
	, loginWidget(new LoginWidget(nullptr))
	, quizWidget(new QuizWidget)
{
	g_terminalControl = this;
	reconnectThread = new ReconnectThread(networkControl->getSocket(), networkControl);
	connect(reconnectThread, &ReconnectThread::information, loginWidget, &LoginWidget::tipLabelSetText);
}

TerminalControl::~TerminalControl()
{

}

void TerminalControl::start()
{
	loginWidget->show();
}
void TerminalControl::Login(const QString &name, const QString &logincode)
{
	LoginPacket *packet(new LoginPacket);
	packet->setName(name);
	packet->setLoginCode(logincode);
	networkControl->send(packet);
	delete packet;
}

void TerminalControl::TestRequest()
{
	TestRequestPacket *packet(new TestRequestPacket);
	networkControl->send(packet);
	delete packet;
}

void TerminalControl::Commit(const int userId, const int subject, const QString &text)
{
	CommitPacket *packet(new CommitPacket);
	packet->setUserId(userId);
	packet->setSubjectNum(subject);
	packet->setText(text);
	networkControl->send(packet);
	delete packet;
}

void TerminalControl::LoginFromServer(const QVariant &data)
{
	unique_ptr<LoginPacket> pakcet(new LoginPacket);
	pakcet->parse(data);
	int userId = pakcet->getUserId();
	quizWidget->setUserId(userId);
}

void TerminalControl::TestRequestFromServer(const QVariant &data)
{
	unique_ptr<TestRequestPacket> packet(new TestRequestPacket);
	packet->parse(data);
	QString title = packet->getTitle();
	QVariantList chapters = packet->getChapter().toVariantList();
	QVariantList subjects = packet->getSubject().toVariantList();
	quizWidget->getTestData(title, chapters, subjects);
}

void TerminalControl::ConfirmationFromServer(const QVariant &data)
{
	unique_ptr<ConfirmationPacket> packet(new ConfirmationPacket);
	packet->parse(data);
	int whichAction = packet->getWhichAction();
	int other = packet->getOther();
	switch (whichAction)
	{
	case NetAction::Login:
		loginWidget->loginSuccess(other, quizWidget.get());
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

void TerminalControl::parsePacketFromByte(const QByteArray &data)
{
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

void TerminalControl::startReconnectThread()
{
	reconnectThread->start();
}
