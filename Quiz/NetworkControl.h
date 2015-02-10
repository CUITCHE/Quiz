#ifndef NETWORKCONTROL_H
#define NETWORKCONTROL_H
#include <QObject>
class QTcpSocket;
class Packet;
class NetworkControl : public QObject
{
	Q_OBJECT
public:
	NetworkControl(QObject *parent = 0);
	~NetworkControl();
	//向服务器提交数据
	void send(Packet *packet);
	//尝试重新连接，阻塞，直到成功
	void reconnect();
	//登陆
	void Login(const QString &name, const QString &logincode);

	//请求test
	void TestRequest();

	//提交填写
	void Commit(const int userId, const int subject, const QString &text);
protected:
	//服务器返回登陆信息
	void LoginFromServer(const QVariant &data);
	//服务器返回 测试卷
	void TestRequestFromServer(const QVariant &data);
	//确认包解析
	void ConfirmationFromServer(const QVariant &data);
protected slots:
	void readPendingDatagrams();
private:
	QTcpSocket *m_socket;
	QString ip;
	qint16 port;
};

#endif // NETWORKCONTROL_H
