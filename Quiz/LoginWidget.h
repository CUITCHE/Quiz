#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <memory>
using namespace std;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QLineEdit;
class LoginWidget : public QWidget
{
	Q_OBJECT

public:
	LoginWidget(QWidget *parent);
	~LoginWidget();
protected:
	QVBoxLayout* iniWidget();
protected slots:
	void confirmBtnClicked();
private:
	unique_ptr<QVBoxLayout> mainLayout;
	QLabel *userNameLabel;
	QLineEdit *userNameInput;
	QLabel *loginCodeLable;
	QLineEdit *loginCodeInput;
	QPushButton *closeBtn;
	QPushButton *confirmBtn;
};

#endif // LOGINWIDGET_H
