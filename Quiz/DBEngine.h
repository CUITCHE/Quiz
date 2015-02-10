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
	//��ʼ�����ݿ⣬�����������ɾ���ؽ�
	void initDB();
protected:
	//������ȫ�������и����ã�
	void createTable();
private:
	static DBEngine *uniqueInstance;
	QMutex mutex;
};

#endif // DBENGINE_H
