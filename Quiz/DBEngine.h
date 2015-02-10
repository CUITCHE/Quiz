#ifndef DBENGINE_H
#define DBENGINE_H
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
class DBEngine : public QThread
{
public:
	DBEngine();
	~DBEngine();
	static DBEngine* instance();
	//初始化数据库，如果表存在则会删表重建
	void initDB();
protected:
	//建表（安全，不会有副作用）
	void createTable();
private:
	static DBEngine *uniqueInstance;
	QMutex mutex;
};

#endif // DBENGINE_H
