#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "TerminalControl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	auto p = DBEngine::instance();
// 	LoginPacket pac("hjq", "3241234");
// 	auto res = pac.parse();
// 	auto json = QJsonDocument::fromVariant(res);
// 	qDebug() << json.toJson();
	unique_ptr<TerminalControl> kernel(new TerminalControl(nullptr));
	kernel->start();
	return a.exec();
}
