#include "stdafx.h"
#include "LoginWidget.h"
#include "NetworkControl.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent)
	, mainLayout(iniWidget())
{

}

LoginWidget::~LoginWidget()
{

}

QVBoxLayout* LoginWidget::iniWidget()
{
	auto layout = new QVBoxLayout;
	QHBoxLayout *row = new QHBoxLayout;
	//row1
	userNameLabel = new QLabel(tr("userName:"));
	userNameInput = new QLineEdit(tr(""));
	row->addWidget(userNameLabel);
	row->addWidget(userNameInput);
	layout->addLayout(row);
	//row2
	row = new QHBoxLayout;
	loginCodeLable = new QLabel(tr("LoginCode:"));
	loginCodeInput = new QLineEdit(tr(""));
	row->addWidget(loginCodeLable);
	row->addWidget(loginCodeInput);
	layout->addLayout(row);
	//row3
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
}

void LoginWidget::confirmBtnClicked()
{
	auto name = userNameInput->text();
	auto code = loginCodeInput->text();
	g_networkControl->Login(name, code);
}
