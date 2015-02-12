#ifndef DBENGINE_H
#define DBENGINE_H
#include <QThread>
#include <utility>
#include <QList>
#include <tuple>
using namespace std;
class QMutex;
class DBEngine : public QThread
{
public:
	DBEngine();
	~DBEngine();
	/*create函数*/

	//************************************
	// Method:    instance
	// FullName:  DBEngine::instance
	// Access:    public static 
	// Returns:   DBEngine*
	// Qualifier: 返回全局唯一DBEngine实体指针
	//************************************
	static DBEngine* instance();

	//************************************
	// Method:    InitDB
	// FullName:  DBEngine::InitDB
	// Access:    public 
	// Returns:   void
	// Qualifier: 初始化数据库，如果表存在则会删表重建
	//************************************
	void ResetDB();

	//************************************
	// Method:    Createtitle
	// FullName:  DBEngine::Createtitle
	// Access:    public 
	// Returns:   pair<bool,int> true,int：创建成功，title的id，否则返回false
	// Qualifier: 创建title：C++知识测验
	// Parameter: const QString & script title：标题的描述
	//************************************
	pair<bool,int> Createtitle(const QString &script);

	//************************************
	// Method:    CreateChapter
	// FullName:  DBEngine::CreateChapter
	// Access:    public 
	// Returns:   pair<bool,int> true,int：创建成功，chapter的id，否则返回false
	// Qualifier: 创建章：第一大题，第二大题等
	// Parameter: const int titleId 标题的id
	// Parameter: const QString & script 章的描述
	//************************************
	pair<bool,int> CreateChapter(const int titleId, const QString &script);

	//************************************
	// Method:    CreateSubject
	// FullName:  DBEngine::CreateSubject
	// Access:    public 
	// Returns:   bool 成功返回true
	// Qualifier: 创建题目subject：C++的创始人？
	// Parameter: const int chapterId 章的id
	// Parameter: const QString & script 题目描述
	// Parameter: const int score 该题的分值
	//************************************
	bool CreateSubject(const int chapterId, const QString &script, const int score);

	//************************************
	// Method:    CreateUser
	// FullName:  DBEngine::CreateUser
	// Access:    public 
	// Returns:   bool 成功返回false
	// Qualifier: 创建一个答题用户
	// Parameter: const QString & userName 用户名字
	// Parameter: const int titleId 用户需要答题的id，不能同时存在多个答题项目
	// Parameter: const QString & loginCode 登录码，相当于密码，由程序自动生成返回。
	//************************************
	bool CreateUser(const QString &userName, const int titleId, const QString &loginCode);

	/*查询....*/

	//返回所有标题
	void AllOfTitle(QList<tuple<int, QString>> &titles);

	//返回所有章
	//int,int,qstring : 章，标题，描述
	void AllOfChapter(QList<tuple<int, int, QString>> &chapters);

	//返回所有用户
	void AllofUsr(QList<tuple<int, QString>> &usrs);

	//返回指定的题目subject
	//chapterId：章；int,qstring,int,题目id，描述，分值
	void SpecifySubject(const int chapterId, tuple<int,QString,int> &subject);

	/*修改....*/
	//修改标题的描述
	bool ModifyTitle(const int titleId, const QString &script);

	//修改章的描述
	bool ModifyChapter(const int chapterId, const QString &script);

	//修改题目，如果score没有被指定值即为默认值时，不修改score的值
	bool ModifySubject(const int subjectId, const QString &script, const int score = -1);

	//用户作答,插入
	bool CreateAnswer(const int user, const int subject, const QString &answer);

	//用户作答,更新
	bool ModifyAnswer(const int user, const int subject, const QString &answer);

	//批卷，插入
	bool CreateComment(const int answer, const int score, const QString &comment);

	//批卷，更新
	bool ModifyComment(const int answer, const pair<bool,int> &score, const pair<bool,QString> &comment);
protected:
	//建表（安全，不会有副作用）
	void createTable();
private:
	static DBEngine *uniqueInstance;
	QMutex *mutex;
};

#endif // DBENGINE_H
