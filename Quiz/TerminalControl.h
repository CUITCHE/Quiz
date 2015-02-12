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
	//登陆
	void Login(const QString &name, const QString &logincode);

	//请求test
	void TestRequest();

	//提交填写
	void Commit(const int userId, const int subject, const QString &text);

	//解析数据
	void parsePacketFromByte(const QByteArray &array);

	//启动重连线程
	void startReconnectThread();
protected:
	void init();
	//服务器返回登陆信息
	void LoginFromServer(const QVariant &data);
	//服务器返回 测试卷
	void TestRequestFromServer(const QVariant &data);
	//确认包解析
	void ConfirmationFromServer(const QVariant &data);
private:
	LoginWidget *loginWidget;
	unique_ptr<QuizWidget> quizWidget;
	NetworkControl *networkControl;
	ReconnectThread *reconnectThread;
};

#endif // TERMINALCONTROL_H
