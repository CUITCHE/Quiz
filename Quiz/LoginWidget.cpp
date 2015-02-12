#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "LoginWidget.h"
#include "NetworkControl.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QCloseEvent>
LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent)
	, mainLayout(iniWidget())
{
	setAttribute(Qt::WA_DeleteOnClose);
}

LoginWidget::~LoginWidget()
{

}

QVBoxLayout* LoginWidget::iniWidget()
{
#define WIDTH 80
	auto layout = new QVBoxLayout;
	QHBoxLayout *row = new QHBoxLayout;
	//row1
	userNameLabel = new QLabel(tr("Your Name:"));
	userNameLabel->setFixedWidth(WIDTH);
	userNameInput = new QLineEdit(tr(""));
	row->addWidget(userNameLabel);
	row->addWidget(userNameInput);
	layout->addLayout(row);
	//row2
	row = new QHBoxLayout;
	loginCodeLable = new QLabel(tr("Login Code:"));
	loginCodeLable->setFixedWidth(WIDTH);
	loginCodeInput = new QLineEdit(tr(""));
	row->addWidget(loginCodeLable);
	row->addWidget(loginCodeInput);
	layout->addLayout(row);
	//row3
	row = new QHBoxLayout;
	tipLabel = new QLabel(tr(""));
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::red);
	tipLabel->setPalette(pa);
	row->addWidget(tipLabel);
	layout->addLayout(row);
	//row4
	row = new QHBoxLayout;
	closeBtn = new QPushButton(tr("Close"));
	confirmBtn = new QPushButton(tr("Confirm"));
	row->addWidget(closeBtn);
	row->addWidget(confirmBtn);
	connect(closeBtn, &QPushButton::clicked, this, &LoginWidget::close);
	connect(confirmBtn, &QPushButton::clicked, this, &LoginWidget::confirmBtnClicked);
	layout->addLayout(row);

	this->setLayout(layout);
	return layout;
#undef WIDTH
}

void LoginWidget::confirmBtnClicked()
{
	auto name = userNameInput->text();
	auto code = loginCodeInput->text();
	g_terminalControl->Login(name, code);
}

void LoginWidget::loginSuccess(int success, QWidget *otherWidget)
{
	QString str;
	switch (success)
	{
	case 0:
		str = tr("µÇÂ½³É¹¦£¡");
		break;
	case 1:
		str = tr("µÇÂ½Ê§°Ü£¡");
		break;
	case 2:
		str = tr("È¨ÏÞ²»¹»£¬½ûÖ¹µÇÂ½£¡");
		break;
	default:
		str = "Î´ÖªÏûÏ¢";
		break;
	}
	tipLabelSetText(str);
	if (success == 0){
		this->close();
		otherWidget->show();
	}
}

void LoginWidget::tipLabelSetText(const QString &text)
{
	if (text.contains("¶Ï¿ª")){
		confirmBtn->setEnabled(false);
	}
	else if (text.contains("»Ö¸´")){
		confirmBtn->setEnabled(true);
	}
	tipLabel->setText(text);
}
