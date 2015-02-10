#include "DBEngine.h"
#include <QtSql/QtSql>
#include <QDebug>
DBEngine* DBEngine::uniqueInstance = nullptr;
DBEngine::DBEngine()
{
	QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
	dbconn.setDatabaseName("examination.db");
	while (!dbconn.open())
	{
		qDebug() << "数据库打开失败，正在重新打开……";
		QThread::sleep(100);
	}
}

DBEngine::~DBEngine()
{

}

DBEngine* DBEngine::instance()
{
	if (uniqueInstance != nullptr){
		return uniqueInstance;
	}
	uniqueInstance = new DBEngine;
	uniqueInstance->createTable();
	return uniqueInstance;
}

void DBEngine::initDB()
{
	QSqlQuery query;
	if (query.exec("drop TABLE tittle;") == false){
		qDebug() << query.lastError();
	}
	if (query.exec("drop TABLE chapter;") == false){
		qDebug() << query.lastError();
	}
	if (query.exec("drop TABLE subject;") == false){
		qDebug() << query.lastError();
	}
	createTable();

}

void DBEngine::createTable()
{
	QSqlQuery query;
	//测试标题表tittle
	//id：主键
	//script：题目文字
	const QString sql1 = "CREATE TABLE IF NOT EXISTS tittle(id INTEGER PRIMARY KEY, script TEXT)";
	if (query.exec(sql1) == false) qDebug() << "tittle表创建失败！";

	//章 表chapter
	//id：主键
	//owner：属于哪个标题tittle
	//script：对章节的描述
	const QString sql2 = "CREATE TABLE IF NOT EXISTS chapter(id INTEGER PRIMARY KEY, owner INTEGER, script TEXT,"
		"FOREIGN KEY(owner) REFERENCES tittle(id))";
	if (query.exec(sql2) == false) qDebug() << "chapter表创建失败！";

	//题目表subject
	//id：主键
	//owner：属于哪一章chapter
	//script：题目的描述
	//score：分值
	//answer：答案，为参考值
	const QString sql3 = "CREATE TABLE IF NOT EXISTS subject(id INTEGER PRIMARY KEY, owner INTEGER, script TEXT,"
		"score INTEGER NOT NULL,answer TEXT, FOREIGN KEY(owner) REFERENCES chapter(id))";
	if (query.exec(sql3) == false) qDebug() << "subject表创建失败！";

	//用户表user
	//id：主键
	//target：这个用户将要答题的编号tittle
	//logincode：登录码（客户端输入登录码后就可以进入）
	//name：用户的名字
	const QString sql4 = "CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY, target INTEGER, logincode CHAR(20),"
		"name CHAR(10),FOREIGN KEY(target) REFERENCES tittle(id))";
	if (query.exec(sql4) == false) qDebug() << "chapter表创建失败！";

	//用户答题后的结果表result
	//id：主键
	//fk_user：来自哪个用户user
	//fk_subject：作答的题目编号subject
	//score：该题得分
	//answer：该题，用户所填答案
	const QString sql5 = "CREATE TABLE IF NOT EXISTS result(id INTEGER PRIMARY KEY, fk_user INTEGER, fk_subject INTEGER,"
		"score INTEGER, answer TEXT, FOREIGN KEY(fk_user) REFERENCES user(id),FOREIGN KEY(fk_subject) REFERENCES subject(id))";
	if (query.exec(sql5) == false) qDebug() << "chapter表创建失败！";
}
