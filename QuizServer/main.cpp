#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "ServerWidget.h"
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	//QByteArray localMsg = msg.toLocal8Bit();
	ServerWidget::publicInstance->sendDebugMsg(msg);
// 	switch (type)
// 	{
// 	case QtDebugMsg:
// 		fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
// 		break;
// 	case QtWarningMsg:
// 		fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
// 		break;
// 	case QtCriticalMsg:
// 		fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
// 		break;
// 	case QtFatalMsg:
// 		fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
// 		abort();
// 	}
}

int main(int argc, char *argv[])
{
	qInstallMessageHandler(myMessageOutput);
	QApplication a(argc, argv);
	
	ServerWidget w;
	qDebug() << "123";
	w.show();
	return a.exec();
}
