#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "ServerWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QFont>
#include <QListWidget>
#include <QFileDialog>
#include <QLineEdit>
ServerWidget *ServerWidget::publicInstance = nullptr;
ServerWidget::ServerWidget(QWidget *parent)
	: QWidget(parent)
	, mainLayout(initWidget())
{
	if (publicInstance == nullptr){
		publicInstance = this;
	}
	g_dbEngine = DBEngine::instance();
	initData();
}

ServerWidget::~ServerWidget()
{

}

void ServerWidget::initData()
{
	//提取所有用户
	auto usrs = g_dbEngine->
}

void ServerWidget::sendDebugMsg(const QString &msg)
{
	debugMsg->insertPlainText(msg);
}

QVBoxLayout* ServerWidget::initWidget()
{
	QVBoxLayout *layout = new QVBoxLayout;
	QHBoxLayout *row;
	//row1
	row = new QHBoxLayout;
	QLabel *label = new QLabel(tr("请选择用户查看答题情况："));
	usersComboBox = new QComboBox;
	connect(usersComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ServerWidget::usersComboBoxChanged);
	addUserBtn = new QPushButton(tr("添加用户"));
	connect(addUserBtn, &QPushButton::clicked, this, &ServerWidget::addUserBtnClicked);
	userOnlineBtn = new QPushButton(tr("查看在线用户"));
	connect(userOnlineBtn, &QPushButton::clicked, this, &ServerWidget::userOnlineBtnClicked);
	row->addWidget(label);
	row->addWidget(usersComboBox);
	row->addWidget(addUserBtn);
	row->addWidget(userOnlineBtn);
	layout->addLayout(row);

	//row2 由3个垂直布局构成
	row = new QHBoxLayout;
	//ver1
	QVBoxLayout *vert = new QVBoxLayout;
	label = new QLabel(tr("未做章节："));
	hasNotDoChapterComboBox = new QComboBox;
	connect(hasNotDoChapterComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ServerWidget::hasNotDoChapterComboBoxChanged);
	hasNotDoListWidget = new QListWidget;
	vert->addWidget(label);
	vert->addWidget(hasNotDoChapterComboBox);
	vert->addWidget(hasNotDoListWidget);
	row->addLayout(vert);
	//ver2
	vert = new QVBoxLayout;
	label = new QLabel(tr("已做章节："));
	alreadyDoChapterComboBox = new QComboBox;
	connect(alreadyDoChapterComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ServerWidget::alreadyDoChapterComboBoxChanged);
	alreadyDoListWidget = new QListWidget;
	connect(alreadyDoListWidget, &QListWidget::itemClicked, this, &ServerWidget::alreadyDoListWidgetItemClicked);
	vert->addWidget(label);
	vert->addWidget(alreadyDoChapterComboBox);
	vert->addWidget(alreadyDoListWidget);
	row->addLayout(vert);
	//ver3
	vert = new QVBoxLayout;
	label = new QLabel(tr("用户作答:"));
	userAlreadyDoText = new QTextEdit;
	userAlreadyDoText->setReadOnly(true);
	vert->addWidget(label);
	vert->addWidget(userAlreadyDoText);

	label = new QLabel(tr("批语："));
	commentInput = new QTextEdit;
	vert->addWidget(label);
	vert->addWidget(commentInput);

	label = new QLabel(tr("评分："));
	scoreInput = new QLineEdit;
	vert->addWidget(label);
	vert->addWidget(scoreInput);
	commentCommitBtn = new QPushButton(tr("提交"));
	connect(commentCommitBtn, &QPushButton::clicked, this, &ServerWidget::commentCommitBtnClicked);
	vert->addWidget(commentCommitBtn);
	row->addLayout(vert);
	layout->addLayout(row);

	//row3
	row = new QHBoxLayout;
	label = new QLabel(tr("添加题目："));
	showAlreadySelectFilePath = new QLineEdit;
	showAlreadySelectFilePath->setReadOnly(true);
	selectFileBtn = new QPushButton(tr("...选择文件"));
	connect(selectFileBtn, &QPushButton::clicked, this, &ServerWidget::selectFileBtnClicked);
	row->addWidget(label);
	row->addWidget(showAlreadySelectFilePath);
	row->addWidget(selectFileBtn);
	layout->addLayout(row);

	//row3
	row = new QHBoxLayout;
	debugMsg = new QTextEdit;
	debugMsg->setReadOnly(true);
	row->addWidget(debugMsg);
	vert = new QVBoxLayout;
	sendRemoteMsgBtn = new QPushButton(tr("发送远程消息"));
	connect(sendRemoteMsgBtn, &QPushButton::clicked, this, &ServerWidget::sendRemoteMsgBtnClicked);
	quitServerBtn = new QPushButton(tr("退出服务"));
	connect(quitServerBtn, &QPushButton::clicked, this, &ServerWidget::quitServerBtnClicked);
	vert->addWidget(sendRemoteMsgBtn);
	vert->addWidget(quitServerBtn);
	row->addLayout(vert);
	layout->addLayout(row);

	this->setLayout(layout);
	return layout;
}

void ServerWidget::usersComboBoxChanged(int index)
{
	//刷新两个list

}

void ServerWidget::addUserBtnClicked()
{
	//弹出用户添加界面，在这里写死。
}

void ServerWidget::userOnlineBtnClicked()
{
	//弹出在线用户列表，直接show一个table
}

void ServerWidget::hasNotDoChapterComboBoxChanged(int index)
{
	//刷新未做章节list
}

void ServerWidget::alreadyDoChapterComboBoxChanged(int index)
{
	//刷新已做章节list
}

void ServerWidget::alreadyDoListWidgetItemClicked(QListWidgetItem *item)
{
	//已做章节list的item被点击，刷新用户作答显示区
}

void ServerWidget::commentCommitBtnClicked()
{
	//提交评论
}

void ServerWidget::selectFileBtnClicked()
{
	//打开一个QFileDialog选择文件，然后对文件进行parse
}

void ServerWidget::sendRemoteMsgBtnClicked()
{
	//发送远程信息
}

void ServerWidget::quitServerBtnClicked()
{
	//安全退出服务
}
