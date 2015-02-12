#ifndef ReconnectThread_H__
#define ReconnectThread_H__
#include <QThread>
class NetworkControl;
class QTcpSocket;
class ReconnectThread :public QThread
{
	Q_OBJECT
public:
	ReconnectThread(QTcpSocket **sock, NetworkControl *parent);
	~ReconnectThread(){}
protected:
	void run();
signals:
	void information(const QString &info);
private:
	QTcpSocket **m_socket;
	NetworkControl *data;
};
#endif // ReconnectThread_H__
