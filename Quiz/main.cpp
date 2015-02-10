#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "QuizWidget.h"
#include "DBEngine.h"
#include "packets/LoginPacket.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	auto p = DBEngine::instance();
// 	LoginPacket pac("hjq", "3241234");
// 	auto res = pac.parse();
// 	auto json = QJsonDocument::fromVariant(res);
// 	qDebug() << json.toJson();
	QuizWidget w;
	w.show();
	return a.exec();
}
