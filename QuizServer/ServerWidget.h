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
	//��½һ���û��󣬾Ͱ�id���������û��б���
	void getLoginUsrId(int usrId);
protected:
	//��ʼ������
	void initData();
public slots:
	//��λ�����������Ϣ�������
	void sendDebugMsg(const QString &msg);
	//�û������б�ı�ۺ���
	void usersComboBoxChanged(int index);
	//����û��ۺ���
	void addUserBtnClicked();
	//�鿴�����û�
	void userOnlineBtnClicked();
	//δ���½�comboBox�ı�
	void hasNotDoChapterComboBoxChanged(int index);
	//�����½�comboBox�ı�
	void alreadyDoChapterComboBoxChanged(int index);
	//�����½��µ�list����ۺ���
	void alreadyDoListWidgetItemClicked(QListWidgetItem *item);
	//�ύ��ť�ۺ���
	void commentCommitBtnClicked();
	//�ļ�ѡ��ť����QFileDialog
	void selectFileBtnClicked();
	//����Զ����Ϣ��ť����
	void sendRemoteMsgBtnClicked();
	//�˳����񣨰�ȫ������
	void quitServerBtnClicked();
protected:
	QVBoxLayout* initWidget();
private:
	unique_ptr<QVBoxLayout> mainLayout;
	QComboBox *usersComboBox;				//�û������б�
	QPushButton *addUserBtn;		//ѡ���û���ȷ����ť
	QPushButton *userOnlineBtn;				//�鿴�û��б�ť
	QComboBox *hasNotDoChapterComboBox;		//δ����
	QListWidget *hasNotDoListWidget;
	QComboBox *alreadyDoChapterComboBox;	//������
	QListWidget *alreadyDoListWidget;
	QTextEdit *userAlreadyDoText;			//��ʾ�û���������
	QTextEdit *commentInput;				//��������
	QLineEdit *scoreInput;					//��������
	QPushButton *commentCommitBtn;			//��������ύ
	QLineEdit *showAlreadySelectFilePath;	//��ʾ�ļ�·��
	QPushButton *selectFileBtn;				//����QFileDialog
	QPushButton *sendRemoteMsgBtn;			//����Զ����Ϣ
	QPushButton *quitServerBtn;			//�˳�
	QTextEdit *debugMsg;			//������Ϣ���
	QList<UserData> usrDataList;			//Ŀǰ�ǵ��˲����Ƕ������
	QList<ChapterData> chapters;			//��
	QMap<int, QList<SubjectData>> chapter_subject_mapper;	//��
public:
	static ServerWidget *publicInstance;
};

#endif // SERVERWIDGET_H
