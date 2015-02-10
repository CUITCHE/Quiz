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
	unique_ptr<QVBoxLayout> mainLayout;
};

#endif // QUIZWIDGET_H
