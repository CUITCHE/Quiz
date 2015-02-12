#ifndef TERMINALCONTROL_H
#define TERMINALCONTROL_H

#include <QObject>
#include <memory>
using namespace std;
class LoginWidget;
class QuizWidget;
class NetworkControl;
class ReconnectThread;
class TerminalControl : public QObject
{
	Q_OBJECT

public:
	TerminalControl(QObject *parent);
	~TerminalControl();
	void start();
	//��½
	void Login(const QString &name, const QString &logincode);

	//����test
	void TestRequest();

	//�ύ��д
	void Commit(const int userId, const int subject, const QString &text);

	//��������
	void parsePacketFromByte(const QByteArray &array);

	//���������߳�
	void startReconnectThread();
protected:
	void init();
	//���������ص�½��Ϣ
	void LoginFromServer(const QVariant &data);
	//���������� ���Ծ�
	void TestRequestFromServer(const QVariant &data);
	//ȷ�ϰ�����
	void ConfirmationFromServer(const QVariant &data);
private:
	LoginWidget *loginWidget;
	unique_ptr<QuizWidget> quizWidget;
	NetworkControl *networkControl;
	ReconnectThread *reconnectThread;
};

#endif // TERMINALCONTROL_H
