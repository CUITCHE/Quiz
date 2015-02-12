#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <memory>
#include "structdefs.h"
using namespace std;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QComboBox;
class QTextEdit;
class QListWidget;
class QLineEdit;
class QFileDialog;
class QListWidgetItem;
class ServerWidget : public QWidget
{
	Q_OBJECT

public:
	ServerWidget(QWidget *parent = 0);
	~ServerWidget();
	//登陆一个用户后，就把id存入在线用户列表中
	void getLoginUsrId(int usrId);
protected:
	//初始化数据
	void initData();
public slots:
	//定位输出到调试信息输出窗口
	void sendDebugMsg(const QString &msg);
	//用户下拉列表改变槽函数
	void usersComboBoxChanged(int index);
	//添加用户槽函数
	void addUserBtnClicked();
	//查看在线用户
	void userOnlineBtnClicked();
	//未做章节comboBox改变
	void hasNotDoChapterComboBoxChanged(int index);
	//已做章节comboBox改变
	void alreadyDoChapterComboBoxChanged(int index);
	//已做章节下的list点击槽函数
	void alreadyDoListWidgetItemClicked(QListWidgetItem *item);
	//提交按钮槽函数
	void commentCommitBtnClicked();
	//文件选择按钮触发QFileDialog
	void selectFileBtnClicked();
	//发送远程信息按钮触发
	void sendRemoteMsgBtnClicked();
	//退出服务（安全操作）
	void quitServerBtnClicked();
protected:
	QVBoxLayout* initWidget();
private:
	unique_ptr<QVBoxLayout> mainLayout;
	QComboBox *usersComboBox;				//用户下拉列表
	QPushButton *addUserBtn;		//选了用户的确定按钮
	QPushButton *userOnlineBtn;				//查看用户列表按钮
	QComboBox *hasNotDoChapterComboBox;		//未做章
	QListWidget *hasNotDoListWidget;
	QComboBox *alreadyDoChapterComboBox;	//已做章
	QListWidget *alreadyDoListWidget;
	QTextEdit *userAlreadyDoText;			//显示用户做的内容
	QTextEdit *commentInput;				//批语输入
	QLineEdit *scoreInput;					//分数输入
	QPushButton *commentCommitBtn;			//批语分数提交
	QLineEdit *showAlreadySelectFilePath;	//显示文件路径
	QPushButton *selectFileBtn;				//触发QFileDialog
	QPushButton *sendRemoteMsgBtn;			//发送远程信息
	QPushButton *quitServerBtn;			//退出
	QTextEdit *debugMsg;			//调试信息输出
	QList<UserData> usrDataList;			//目前是单人不考虑多人情况
	QList<ChapterData> chapters;			//章
	QMap<int, QList<SubjectData>> chapter_subject_mapper;	//节
public:
	static ServerWidget *publicInstance;
};

#endif // SERVERWIDGET_H
