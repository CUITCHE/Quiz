#include "QuizWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QComboBox>
#include <QTextEdit>
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
	//row1
	QHBoxLayout *row1 = new QHBoxLayout;
	themeLabel = new QLabel(tr("Default"));
	row1->addWidget(themeLabel);
	row1->setAlignment(Qt::AlignCenter);
	//row2
	QHBoxLayout *row2 = new QHBoxLayout;
	chapteLabel = new QLabel(tr("Chapter:"));
	chapterCombo = new QComboBox;
	row2->addWidget(chapteLabel);
	row2->addWidget(chapterCombo);
	//row3
	QHBoxLayout *row3 = new QHBoxLayout;
	subjectLabel = new QLabel(tr("Subject:"));
	subjectText = new QTextEdit;
	row3->addWidget(subjectLabel);
	row3->addWidget(subjectText);
	//row4
	QHBoxLayout *row4 = new QHBoxLayout;
	inputLabel = new QLabel(tr("Write:"));
	inputEdit = new QTextEdit;
	row4->addWidget(inputLabel);
	row4->addWidget(inputEdit);
	//row5
	QHBoxLayout *row5 = new QHBoxLayout;
	forwardBtn = new QPushButton(tr("&Forward"));
	nextBtn = new QPushButton(tr("&Back"));
	resetBtn = new QPushButton(tr("&Reset"));
	submitBtn = new QPushButton(tr("&Submit"));
	connect(forwardBtn, &QAbstractButton::clicked, this, &QuizWidget::forwardBtnClicked);
	connect(nextBtn, &QAbstractButton::clicked, this, &QuizWidget::nextBtnClicked);
	connect(resetBtn, &QAbstractButton::clicked, this, &QuizWidget::resetBtnClicked);
	connect(submitBtn, &QAbstractButton::clicked, this, &QuizWidget::submitBtnClicked);
	row5->addWidget(forwardBtn);
	row5->addWidget(nextBtn);
	row5->addWidget(resetBtn);
	row5->addWidget(submitBtn);
	//main layout
	QVBoxLayout *_mainLayout = new QVBoxLayout;
	_mainLayout->addLayout(row1);
	_mainLayout->addLayout(row2);
	_mainLayout->addLayout(row3);
	_mainLayout->addLayout(row4);
	_mainLayout->addLayout(row5);
	this->setLayout(_mainLayout);
	return _mainLayout;
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
