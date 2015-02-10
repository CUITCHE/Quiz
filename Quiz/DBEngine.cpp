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
		qDebug() << "���ݿ��ʧ�ܣ��������´򿪡���";
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
	//���Ա����tittle
	//id������
	//script����Ŀ����
	const QString sql1 = "CREATE TABLE IF NOT EXISTS tittle(id INTEGER PRIMARY KEY, script TEXT)";
	if (query.exec(sql1) == false) qDebug() << "tittle����ʧ�ܣ�";

	//�� ��chapter
	//id������
	//owner�������ĸ�����tittle
	//script�����½ڵ�����
	const QString sql2 = "CREATE TABLE IF NOT EXISTS chapter(id INTEGER PRIMARY KEY, owner INTEGER, script TEXT,"
		"FOREIGN KEY(owner) REFERENCES tittle(id))";
	if (query.exec(sql2) == false) qDebug() << "chapter����ʧ�ܣ�";

	//��Ŀ��subject
	//id������
	//owner��������һ��chapter
	//script����Ŀ������
	//score����ֵ
	//answer���𰸣�Ϊ�ο�ֵ
	const QString sql3 = "CREATE TABLE IF NOT EXISTS subject(id INTEGER PRIMARY KEY, owner INTEGER, script TEXT,"
		"score INTEGER NOT NULL,answer TEXT, FOREIGN KEY(owner) REFERENCES chapter(id))";
	if (query.exec(sql3) == false) qDebug() << "subject����ʧ�ܣ�";

	//�û���user
	//id������
	//target������û���Ҫ����ı��tittle
	//logincode����¼�루�ͻ��������¼���Ϳ��Խ��룩
	//name���û�������
	const QString sql4 = "CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY, target INTEGER, logincode CHAR(20),"
		"name CHAR(10),FOREIGN KEY(target) REFERENCES tittle(id))";
	if (query.exec(sql4) == false) qDebug() << "chapter����ʧ�ܣ�";

	//�û������Ľ����result
	//id������
	//fk_user�������ĸ��û�user
	//fk_subject���������Ŀ���subject
	//score������÷�
	//answer�����⣬�û������
	const QString sql5 = "CREATE TABLE IF NOT EXISTS result(id INTEGER PRIMARY KEY, fk_user INTEGER, fk_subject INTEGER,"
		"score INTEGER, answer TEXT, FOREIGN KEY(fk_user) REFERENCES user(id),FOREIGN KEY(fk_subject) REFERENCES subject(id))";
	if (query.exec(sql5) == false) qDebug() << "chapter����ʧ�ܣ�";
}
