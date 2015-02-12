#pragma execution_character_set("utf-8")
#include "stdafx.h"
#include "DBEngine.h"
#include <QtSql/QtSql>
#include <QMutexLocker>
DBEngine* DBEngine::uniqueInstance = nullptr;
#define __lock__ QMutexLocker locker(mutex);
DBEngine::DBEngine()
	:mutex(new QMutex)
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

void DBEngine::ResetDB()
{
	QSqlQuery query;
	if (query.exec("drop TABLE title;") == false){
		qDebug() << query.lastError();
	}
	if (query.exec("drop TABLE chapter;") == false){
		qDebug() << query.lastError();
	}
	if (query.exec("drop TABLE subject;") == false){
		qDebug() << query.lastError();
	}
	if (query.exec("drop TABLE user;") == false){
		qDebug() << query.lastError();
	}
	if (query.exec("drop TABLE result;") == false){
		qDebug() << query.lastError();
	}
	if (query.exec("drop TABLE answer;") == false){
		qDebug() << query.lastError();
	}
	createTable();

}

void DBEngine::createTable()
{
	QSqlQuery query;
	//���Ա����title
	//id������
	//script����Ŀ����
	const QString sql1 = "CREATE TABLE IF NOT EXISTS title(id INTEGER PRIMARY KEY, script TEXT)";
	if (query.exec(sql1) == false) {
		qDebug() << "title����ʧ�ܣ�" << query.lastError();
	}

	//�� ��chapter
	//id������
	//owner�������ĸ�����title
	//script�����½ڵ�����
	const QString sql2 = "CREATE TABLE IF NOT EXISTS chapter(id INTEGER PRIMARY KEY, owner INTEGER, script TEXT,"
		"FOREIGN KEY(owner) REFERENCES title(id))";
	if (query.exec(sql2) == false) {
		qDebug() << "chapter����ʧ�ܣ�" << query.lastError();
	}

	//��Ŀ��subject
	//id������
	//owner��������һ��chapter
	//script����Ŀ������
	//score����ֵ
	//answer���𰸣�Ϊ�ο�ֵ
	const QString sql3 = "CREATE TABLE IF NOT EXISTS subject(id INTEGER PRIMARY KEY, owner INTEGER, script TEXT,"
		"score INTEGER NOT NULL,answer TEXT, FOREIGN KEY(owner) REFERENCES chapter(id))";
	if (query.exec(sql3) == false) {
		qDebug() << "subject����ʧ�ܣ�" << query.lastError();
	}

	//�û���user
	//id������
	//target������û���Ҫ����ı��title
	//logincode����¼�루�ͻ��������¼���Ϳ��Խ��룩
	//name���û�������
	const QString sql4 = "CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY, target INTEGER, logincode CHAR(20),"
		"name CHAR(10),FOREIGN KEY(target) REFERENCES title(id))";
	if (query.exec(sql4) == false) {
		qDebug() << "user����ʧ�ܣ�" << query.lastError();
	}

	//����û�����ı�answer
	//id������
	//fk_user�������ĸ��û�user
	//fk_subject���������Ŀ���subject
	//ret����
	const QString sql5 = "CREATE TABLE IF NOT EXISTS answer(id INTEGER PRIMARY KEY, fk_user INTEGER, fk_subject INTEGER,"
		"ret TEXT,FOREIGN KEY(fk_user) REFERENCES user(id),FOREIGN KEY(fk_subject) REFERENCES subject(id)) ";
	if (query.exec(sql5) == false) {
		qDebug() << "answer����ʧ�ܣ�" << query.lastError();
	}

	//�û������Ľ����result
	//id������
	//fk_answer�������ķݶ���answer
	//score������÷�
	//comment�����⣬�����߸�������
	const QString sql6 = "CREATE TABLE IF NOT EXISTS result(id INTEGER PRIMARY KEY, fk_answer INTEGER, score INTEGER,"
		"comment TEXT, FOREIGN KEY(fk_answer) REFERENCES answer(id))";
	if (query.exec(sql6) == false) {
		qDebug() << "result����ʧ�ܣ�" << query.lastError();
	}

	
}

pair<bool, int> DBEngine::Createtitle(const QString &script)
{
	QSqlQuery query;
	QString sql = QString("insert into title(script) values('%1')").arg(script);
	if (query.exec(sql) == false){
		qDebug() << "����title��ʧ��" << query.lastError();
		return pair<bool, int>(false, 0);
	}
	sql = QString("select id from title order by id desc limit 1");
	if (query.exec(sql) == true){
		while (query.next()){
			return pair<bool, int>(true, query.value("id").toInt());
		}
	}
	else{
		qDebug() << "select title���һ��ʧ��" << query.lastError();
	}
	return pair<bool, int>(false, 0);
}

pair<bool, int> DBEngine::CreateChapter(const int titleId, const QString &script)
{
	QSqlQuery query;
	QString sql = QString("insert into chapter(owner,script) values(%1,'%2')").arg(titleId).arg(script);
	if (query.exec(sql) == false){
		qDebug() << "����chapter��ʧ��" << query.lastError();
		return pair<bool, int>(false, 0);
	}
	sql = QString("select id from chapter order by id desc limit 1");
	if (query.exec(sql) == true){
		while (query.next()){
			return pair<bool, int>(true, query.value("id").toInt());
		}
	}
	else{
		qDebug() << "select chapter���һ��ʧ��" << query.lastError();
	}
	return pair<bool, int>(false,0);
}

bool DBEngine::CreateSubject(const int chapterId, const QString &script, const int score)
{
	
	QSqlQuery query;
	QString sql = QString("insert into subject(owner,script,score) values(1%,'%2',%3)").arg(chapterId).arg(script).arg(score);
	if (query.exec(sql) == false){
		qDebug() << "���� subject��ʧ��" << query.lastError();
		return false;
	}
	return true;
}

bool DBEngine::CreateUser(const QString &userName, const int titleId, const QString &loginCode)
{
	QSqlQuery query;
	QString sql = QString("select id from user where name = '1%'").arg(userName);
	if (query.exec(sql) == true){
		if (query.next()){
			qDebug() << "�����ظ����" << userName << ",Ҫ��֤����Ψһ";
			return false;
		}
	}
	sql = QString("insert into user(target,logincode,name) values(1%,'%2','%3')").arg(titleId).arg(loginCode).arg(userName);
	if (query.exec(sql) == false){
		qDebug() << "���� user��ʧ��" << query.lastError();
		return false;
	}
	return true;
}

void DBEngine::AllOfTitle(QList<tuple<int, QString>> &titles)
{
	QSqlQuery query;
	QString sql = QString("select * from title");
	if (query.exec(sql) == false){
		qDebug() << "��ѯ����titleʧ��" << query.lastError();
		return;
	}
	int id;
	QString script;
	while (query.next()){
		id = query.value("id").toInt();
		script = query.value("script").toString();
		titles.push_back(make_tuple(id, script));
	}
}

void DBEngine::AllOfChapter(QList<tuple<int, int, QString>> &chapters)
{
	QSqlQuery query;
	QString sql = QString("select * from chapter");
	if (query.exec(sql) == false){
		qDebug() << "��ѯ����chapterʧ��" << query.lastError();
		return;
	}
	int id;
	int owner;
	QString script;
	while (query.next()){
		id = query.value("id").toInt();
		owner = query.value("owner").toInt();
		script = query.value("script").toString();
		chapters.push_back(make_tuple(id, owner, script));
	}
}

void DBEngine::AllofUsr(QList<tuple<int, QString>> &usrs)
{
	QSqlQuery query;
	QString sql = QString("select * from chapter");
}

void DBEngine::SpecifySubject(const int chapterId, tuple<int, QString, int> &subject)
{
	QSqlQuery query;
	QString sql = QString("select id,script,score from subject where owner = %1").arg(chapterId);
	if (query.exec(sql) == false){
		qDebug() << "��ѯָ��������subjectʧ��" << query.lastError();
		return;
	}
	int id;
	QString script;
	int score;
	if (query.next()){
		id = query.value("id").toInt();
		script = query.value("script").toString();
		score = query.value("score").toInt();
		subject = make_tuple(id, script, score);
	}
}

bool DBEngine::ModifyTitle(const int titleId, const QString &script)
{
	QSqlQuery query;
	QString sql = QString("update title set script = '%1' where id = %2").arg(script).arg(titleId);
	if (query.exec(sql) == false){
		qDebug() << "update title failed." << query.lastError();
		return false;
	}
	return true;
}

bool DBEngine::ModifyChapter(const int chapterId, const QString &script)
{
	QSqlQuery query;
	QString sql = QString("update chapter set script = '%1' where id = %2").arg(script).arg(chapterId);
	if (query.exec(sql) == false){
		qDebug() << "update chapter failed." << query.lastError();
		return false;
	}
	return true;
}

bool DBEngine::ModifySubject(const int subjectId, const QString &script, const int score /*= -1*/)
{
	QSqlQuery query;
	QString sql = QString("update subject set script = %1 %2 where id = %3").arg(script).arg(score == -1 ? "" : QString(",score = %1").arg(score)).arg(subjectId);
	if (query.exec(sql) == false){
		qDebug() << "update subject failed." << query.lastError();
		return false;
	}
	return true;
}

bool DBEngine::CreateAnswer(const int user, const int subject, const QString &answer)
{
	QSqlQuery query;
	QString sql = QString("select id from answer where fk_subject = %1").arg(subject);
	//��ѯ�Ƿ��Ѿ������������������޸�ֵ
	if (query.exec(sql) == false){
		qDebug() << "select answer failed." << query.lastError();
		return false;
	}
	bool ok = query.next();
	if (ok == true){
		qDebug() << "����answerʧ�ܣ��Ѵ��ڶ�ָ����Ŀ�Ĵ𰸣������ظ�";
		return false;
	}
	sql = QString("insert into answer(fk_user,fk_subject,ret) values(%1,%2,'%3')").arg(user).arg(subject).arg(answer);
	if (query.exec(sql) == false){
		qDebug() << "����answer��ʧ��" << query.lastError();
		return false;
	}
	return true;
}

bool DBEngine::ModifyAnswer(const int user, const int subject, const QString &answer)
{
	QSqlQuery query;
	QString sql = QString("update answer set ret = %1 where fk_user = %2 and fk_subject = %3").arg(answer).arg(user).arg(subject);
	if (query.exec(sql) == false){
		qDebug() << "����answer��ʧ��" << query.lastError();
		return false;
	}
	return true;
}

bool DBEngine::CreateComment(const int answer, const int score, const QString &comment)
{
	QSqlQuery query;
	QString sql = QString("select id from result where fk_answer = %1").arg(answer);
	//��ѯ�Ƿ����������������͸���ֵ
	if (query.exec(sql) == false){
		qDebug() << "select result failed" << query.lastError();
		return false;
	}
	bool ok = query.next();
	if (ok == true){
		qDebug() << "����resultʧ�ܣ��Ѵ��ڶ�ָ����Ŀ����������ظ�";
		return false;
	}
	sql = QString("insert into result(fk_answer,score,comment) values(%1,%2,'%3')").arg(answer).arg(score).arg(comment);
	if (query.exec(sql) == false){
		qDebug() << "����result��ʧ��" << query.lastError();
		return false;
	}
	return false;
}

bool DBEngine::ModifyComment(const int answer, const pair<bool, int> &score, const pair<bool, QString> &comment)
{
	QSqlQuery query;
	QString sql;
	if (score.first == true){
		sql = QString("update result set score = %1 where fk_answer = %2").arg(score.second).arg(answer);
		if (query.exec(sql) == false){
			qDebug() << "����result��ʧ��" << query.lastError();
			return false;
		}
	}
	if (comment.first == true){
		sql = QString("update result set comment = %1 where fk_answer = %2").arg(comment.second).arg(answer);
		if (query.exec(sql) == false){
			qDebug() << "����result��ʧ��" << query.lastError();
			return false;
		}
	}
	
	return true;
}
