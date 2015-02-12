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
	//��ȡ�����û�
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
	QLabel *label = new QLabel(tr("��ѡ���û��鿴���������"));
	usersComboBox = new QComboBox;
	connect(usersComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ServerWidget::usersComboBoxChanged);
	addUserBtn = new QPushButton(tr("����û�"));
	connect(addUserBtn, &QPushButton::clicked, this, &ServerWidget::addUserBtnClicked);
	userOnlineBtn = new QPushButton(tr("�鿴�����û�"));
	connect(userOnlineBtn, &QPushButton::clicked, this, &ServerWidget::userOnlineBtnClicked);
	row->addWidget(label);
	row->addWidget(usersComboBox);
	row->addWidget(addUserBtn);
	row->addWidget(userOnlineBtn);
	layout->addLayout(row);

	//row2 ��3����ֱ���ֹ���
	row = new QHBoxLayout;
	//ver1
	QVBoxLayout *vert = new QVBoxLayout;
	label = new QLabel(tr("δ���½ڣ�"));
	hasNotDoChapterComboBox = new QComboBox;
	connect(hasNotDoChapterComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ServerWidget::hasNotDoChapterComboBoxChanged);
	hasNotDoListWidget = new QListWidget;
	vert->addWidget(label);
	vert->addWidget(hasNotDoChapterComboBox);
	vert->addWidget(hasNotDoListWidget);
	row->addLayout(vert);
	//ver2
	vert = new QVBoxLayout;
	label = new QLabel(tr("�����½ڣ�"));
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
	label = new QLabel(tr("�û�����:"));
	userAlreadyDoText = new QTextEdit;
	userAlreadyDoText->setReadOnly(true);
	vert->addWidget(label);
	vert->addWidget(userAlreadyDoText);

	label = new QLabel(tr("���"));
	commentInput = new QTextEdit;
	vert->addWidget(label);
	vert->addWidget(commentInput);

	label = new QLabel(tr("���֣�"));
	scoreInput = new QLineEdit;
	vert->addWidget(label);
	vert->addWidget(scoreInput);
	commentCommitBtn = new QPushButton(tr("�ύ"));
	connect(commentCommitBtn, &QPushButton::clicked, this, &ServerWidget::commentCommitBtnClicked);
	vert->addWidget(commentCommitBtn);
	row->addLayout(vert);
	layout->addLayout(row);

	//row3
	row = new QHBoxLayout;
	label = new QLabel(tr("�����Ŀ��"));
	showAlreadySelectFilePath = new QLineEdit;
	showAlreadySelectFilePath->setReadOnly(true);
	selectFileBtn = new QPushButton(tr("...ѡ���ļ�"));
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
	sendRemoteMsgBtn = new QPushButton(tr("����Զ����Ϣ"));
	connect(sendRemoteMsgBtn, &QPushButton::clicked, this, &ServerWidget::sendRemoteMsgBtnClicked);
	quitServerBtn = new QPushButton(tr("�˳�����"));
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
	//ˢ������list

}

void ServerWidget::addUserBtnClicked()
{
	//�����û���ӽ��棬������д����
}

void ServerWidget::userOnlineBtnClicked()
{
	//���������û��б�ֱ��showһ��table
}

void ServerWidget::hasNotDoChapterComboBoxChanged(int index)
{
	//ˢ��δ���½�list
}

void ServerWidget::alreadyDoChapterComboBoxChanged(int index)
{
	//ˢ�������½�list
}

void ServerWidget::alreadyDoListWidgetItemClicked(QListWidgetItem *item)
{
	//�����½�list��item�������ˢ���û�������ʾ��
}

void ServerWidget::commentCommitBtnClicked()
{
	//�ύ����
}

void ServerWidget::selectFileBtnClicked()
{
	//��һ��QFileDialogѡ���ļ���Ȼ����ļ�����parse
}

void ServerWidget::sendRemoteMsgBtnClicked()
{
	//����Զ����Ϣ
}

void ServerWidget::quitServerBtnClicked()
{
	//��ȫ�˳�����
}
