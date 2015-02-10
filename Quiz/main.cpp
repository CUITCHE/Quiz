#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include "QuizWidget.h"
#include "DBEngine.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QuizWidget w;
	w.show();
	return a.exec();
}
