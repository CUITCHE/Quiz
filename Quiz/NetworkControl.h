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
	//��������ύ����
	void send(Packet *packet);
	//�����������ӣ�������ֱ���ɹ�
	void reconnect();
	//��½
	void Login(const QString &name, const QString &logincode);

	//����test
	void TestRequest();

	//�ύ��д
	void Commit(const int userId, const int subject, const QString &text);
protected:
	//���������ص�½��Ϣ
	void LoginFromServer(const QVariant &data);
	//���������� ���Ծ�
	void TestRequestFromServer(const QVariant &data);
	//ȷ�ϰ�����
	void ConfirmationFromServer(const QVariant &data);
protected slots:
	void readPendingDatagrams();
private:
	QTcpSocket *m_socket;
	QString ip;
	qint16 port;
};

#endif // NETWORKCONTROL_H
