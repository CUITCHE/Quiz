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
	//从服务器获得测试卷数据
	void getTestData(const QString &title, const QVariantList &c, const QVariantList &s);
	//设置user id
	void setUserId(int id){ usrId = id; }
protected slots:
	void forwardBtnClicked();
	void nextBtnClicked();
	void resetBtnClicked();
	void submitBtnClicked();
protected:
	QVBoxLayout* initWidget();
private:
	QLabel *themeLabel;		//主题label
	QLabel *chapteLabel;	//章
	QLabel *subjectLabel;	//题目
	QLabel *inputLabel;	//作答
	QComboBox *chapterCombo;	//章选择下拉框
	QTextEdit *subjectText;		//题目显示框
	QTextEdit *inputEdit;	//作答输入框
	QPushButton *forwardBtn;	//前一道题
	QPushButton *nextBtn;		//后一道题
	QPushButton *submitBtn;		//提交当前题目
	QPushButton *resetBtn;		//重置输入框
	QLabel *lastWriteLable;		//last write label;
	QTextEdit *lastWriteEdit;	//last write edit;
	QLabel *commentLable;		//comment lable
	QTextEdit *commentEdit;		//comment 显示框
	QLabel *nowChapterTottal;	//当前chapter共有n个subject，当前是第m个subject
	unique_ptr<QVBoxLayout> mainLayout;
	QList<shared_ptr<ChapterData>> chapters;
	QList<shared_ptr<SubjectData >> subjects;
	QMap<int, QList<shared_ptr<SubjectData>>> c_s_mapper;		//章节id映射subject
	QList<shared_ptr<SubjectData>> currentSelectChapter;		//当前选择的章的所有题目
	int pointer_subject;							//题目指针。
	int usrId;
};

#endif // QUIZWIDGET_H
