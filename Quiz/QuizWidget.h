#ifndef QUIZWIDGET_H
#define QUIZWIDGET_H

#include "structdefs.h"
#include <QWidget>
#include <memory>
#include <QList>
#include <QMap>
using namespace std;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QComboBox;
class QTextEdit;
class QuizWidget : public QWidget
{
	Q_OBJECT

public:
	QuizWidget(QWidget *parent = 0);
	~QuizWidget();
	//�ӷ�������ò��Ծ�����
	void getTestData(const QString &title, const QVariantList &c, const QVariantList &s);
	//����user id
	void setUserId(int id){ usrId = id; }
protected slots:
	void forwardBtnClicked();
	void nextBtnClicked();
	void resetBtnClicked();
	void submitBtnClicked();
protected:
	QVBoxLayout* initWidget();
private:
	QLabel *themeLabel;		//����label
	QLabel *chapteLabel;	//��
	QLabel *subjectLabel;	//��Ŀ
	QLabel *inputLabel;	//����
	QComboBox *chapterCombo;	//��ѡ��������
	QTextEdit *subjectText;		//��Ŀ��ʾ��
	QTextEdit *inputEdit;	//���������
	QPushButton *forwardBtn;	//ǰһ����
	QPushButton *nextBtn;		//��һ����
	QPushButton *submitBtn;		//�ύ��ǰ��Ŀ
	QPushButton *resetBtn;		//���������
	QLabel *lastWriteLable;		//last write label;
	QTextEdit *lastWriteEdit;	//last write edit;
	QLabel *commentLable;		//comment lable
	QTextEdit *commentEdit;		//comment ��ʾ��
	QLabel *nowChapterTottal;	//��ǰchapter����n��subject����ǰ�ǵ�m��subject
	unique_ptr<QVBoxLayout> mainLayout;
	QList<shared_ptr<ChapterData>> chapters;
	QList<shared_ptr<SubjectData >> subjects;
	QMap<int, QList<shared_ptr<SubjectData>>> c_s_mapper;		//�½�idӳ��subject
	QList<shared_ptr<SubjectData>> currentSelectChapter;		//��ǰѡ����µ�������Ŀ
	int pointer_subject;							//��Ŀָ�롣
	int usrId;
};

#endif // QUIZWIDGET_H
