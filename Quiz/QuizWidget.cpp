#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "QuizWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QFont>
QuizWidget::QuizWidget(QWidget *parent)
	: QWidget(parent)
	, mainLayout(initWidget())
{

}

QuizWidget::~QuizWidget()
{

}

QVBoxLayout* QuizWidget::initWidget()
{
	//main layout
	QVBoxLayout *_mainLayout = new QVBoxLayout;
	
#define WIDTH 50
	//row1
	QHBoxLayout *row = new QHBoxLayout;
	themeLabel = new QLabel(tr("Default"));
	QFont font;
	font.setFamily("Î¢ÈíÑÅºÚ");
	font.setBold(true);
	font.setPixelSize(18);
	themeLabel->setFont(font);
	row->addWidget(themeLabel);
	row->setAlignment(Qt::AlignCenter);
	_mainLayout->addLayout(row);
	//row2
	row = new QHBoxLayout;
	row->setAlignment(Qt::AlignLeft);
	chapteLabel = new QLabel(tr("Chapter:"));
	chapteLabel->setFixedWidth(WIDTH);
	chapterCombo = new QComboBox;
	chapterCombo->setFixedWidth(230);
	nowChapterTottal = new QLabel(tr(""));
	row->addWidget(chapteLabel);
	row->addWidget(chapterCombo);
	row->addWidget(nowChapterTottal);
	_mainLayout->addLayout(row);
	//row3
	row = new QHBoxLayout;
	subjectLabel = new QLabel(tr("Subject:"));
	subjectLabel->setFixedWidth(WIDTH);
	subjectText = new QTextEdit;
	subjectText->setReadOnly(true);
	commentLable = new QLabel(tr("Comment:"));
	commentLable->setFixedWidth(WIDTH);
	commentEdit = new QTextEdit;
	commentEdit->setReadOnly(true);
	row->addWidget(subjectLabel);
	row->addWidget(subjectText);
	row->addWidget(commentLable);
	row->addWidget(commentEdit);
	_mainLayout->addLayout(row);
	//row4
	row = new QHBoxLayout;
	lastWriteLable = new QLabel(tr("Last Write:"));
	lastWriteLable->setWordWrap(true);
	lastWriteLable->setFixedWidth(WIDTH);
	lastWriteEdit = new QTextEdit;
	lastWriteEdit->setReadOnly(true);
	row->addWidget(lastWriteLable);
	row->addWidget(lastWriteEdit);
	_mainLayout->addLayout(row);

	//row5
	row = new QHBoxLayout;
	inputLabel = new QLabel(tr("Write Here:"));
	inputLabel->setFixedWidth(WIDTH * 2);
	row->setAlignment(Qt::AlignLeft);
	row->addWidget(inputLabel);
	_mainLayout->addLayout(row);
	//row6
	row = new QHBoxLayout;
	inputEdit = new QTextEdit;
	row->addWidget(inputEdit);
	_mainLayout->addLayout(row);
	//row7
	row = new QHBoxLayout;
	forwardBtn = new QPushButton(tr("< &Forward"));
	nextBtn = new QPushButton(tr("&Back >"));
	resetBtn = new QPushButton(tr("&Reset"));
	submitBtn = new QPushButton(tr("&Submit"));
	connect(forwardBtn, &QAbstractButton::clicked, this, &QuizWidget::forwardBtnClicked);
	connect(nextBtn, &QAbstractButton::clicked, this, &QuizWidget::nextBtnClicked);
	connect(resetBtn, &QAbstractButton::clicked, this, &QuizWidget::resetBtnClicked);
	connect(submitBtn, &QAbstractButton::clicked, this, &QuizWidget::submitBtnClicked);
	row->addWidget(forwardBtn);
	row->addWidget(nextBtn);
	row->addWidget(resetBtn);
	row->addWidget(submitBtn);
	_mainLayout->addLayout(row);

	this->setLayout(_mainLayout);
	return _mainLayout;
#undef WIDTH
}

void QuizWidget::forwardBtnClicked()
{

}

void QuizWidget::nextBtnClicked()
{

}

void QuizWidget::resetBtnClicked()
{

}

void QuizWidget::submitBtnClicked()
{

}
