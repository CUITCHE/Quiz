#ifndef QUIZWIDGET_H
#define QUIZWIDGET_H

#include <QWidget>
#include <memory>
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
	unique_ptr<QVBoxLayout> mainLayout;
};

#endif // QUIZWIDGET_H
