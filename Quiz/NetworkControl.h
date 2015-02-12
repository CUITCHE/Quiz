#ifndef NETWORKCONTROL_H
#define NETWORKCONTROL_H
#include <QThread>
class QTcpSocket;
class Packet;
class QEvent;
class NetworkControl : public QObject
{
	Q_OBJECT
	friend class ReconnectThread;
public:
	NetworkControl(QObject *parent = 0);
	~NetworkControl();

	//��������ύ����
	void send(Packet *packet);
	//�����������ӣ�������ֱ���ɹ�
	bool reconnect();
	QTcpSocket** getSocket(){ return &m_socket; }
protected:
	//��ȡsettin.json����
	void getIpAndPortFromLocalJsonFile();
	
protected slots:
	void readPendingDatagrams();
private:
	QTcpSocket *m_socket;
	QString ip;
	qint16 port;
};

#endif // NETWORKCONTROL_H
