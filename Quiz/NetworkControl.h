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

	//向服务器提交数据
	void send(Packet *packet);
	//尝试重新连接，阻塞，直到成功
	bool reconnect();
	QTcpSocket** getSocket(){ return &m_socket; }
protected:
	//读取settin.json配置
	void getIpAndPortFromLocalJsonFile();
	
protected slots:
	void readPendingDatagrams();
private:
	QTcpSocket *m_socket;
	QString ip;
	qint16 port;
};

#endif // NETWORKCONTROL_H
