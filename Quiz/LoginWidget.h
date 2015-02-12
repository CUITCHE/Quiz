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
	void loginSuccess(int success, QWidget *otherWidget);
protected:
	QVBoxLayout* iniWidget();
public slots :
	void confirmBtnClicked();
	void tipLabelSetText(const QString &text);
private:
	unique_ptr<QVBoxLayout> mainLayout;
	QLabel *userNameLabel;
	QLineEdit *userNameInput;
	QLabel *loginCodeLable;
	QLineEdit *loginCodeInput;
	QPushButton *closeBtn;
	QPushButton *confirmBtn;
	QLabel *tipLabel;
};

#endif // LOGINWIDGET_H
