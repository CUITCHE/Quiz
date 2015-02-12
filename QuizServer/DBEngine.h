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
	/*create����*/

	//************************************
	// Method:    instance
	// FullName:  DBEngine::instance
	// Access:    public static 
	// Returns:   DBEngine*
	// Qualifier: ����ȫ��ΨһDBEngineʵ��ָ��
	//************************************
	static DBEngine* instance();

	//************************************
	// Method:    InitDB
	// FullName:  DBEngine::InitDB
	// Access:    public 
	// Returns:   void
	// Qualifier: ��ʼ�����ݿ⣬�����������ɾ���ؽ�
	//************************************
	void ResetDB();

	//************************************
	// Method:    Createtitle
	// FullName:  DBEngine::Createtitle
	// Access:    public 
	// Returns:   pair<bool,int> true,int�������ɹ���title��id�����򷵻�false
	// Qualifier: ����title��C++֪ʶ����
	// Parameter: const QString & script title�����������
	//************************************
	pair<bool,int> Createtitle(const QString &script);

	//************************************
	// Method:    CreateChapter
	// FullName:  DBEngine::CreateChapter
	// Access:    public 
	// Returns:   pair<bool,int> true,int�������ɹ���chapter��id�����򷵻�false
	// Qualifier: �����£���һ���⣬�ڶ������
	// Parameter: const int titleId �����id
	// Parameter: const QString & script �µ�����
	//************************************
	pair<bool,int> CreateChapter(const int titleId, const QString &script);

	//************************************
	// Method:    CreateSubject
	// FullName:  DBEngine::CreateSubject
	// Access:    public 
	// Returns:   bool �ɹ�����true
	// Qualifier: ������Ŀsubject��C++�Ĵ�ʼ�ˣ�
	// Parameter: const int chapterId �µ�id
	// Parameter: const QString & script ��Ŀ����
	// Parameter: const int score ����ķ�ֵ
	//************************************
	bool CreateSubject(const int chapterId, const QString &script, const int score);

	//************************************
	// Method:    CreateUser
	// FullName:  DBEngine::CreateUser
	// Access:    public 
	// Returns:   bool �ɹ�����false
	// Qualifier: ����һ�������û�
	// Parameter: const QString & userName �û�����
	// Parameter: const int titleId �û���Ҫ�����id������ͬʱ���ڶ��������Ŀ
	// Parameter: const QString & loginCode ��¼�룬�൱�����룬�ɳ����Զ����ɷ��ء�
	//************************************
	bool CreateUser(const QString &userName, const int titleId, const QString &loginCode);

	/*��ѯ....*/

	//�������б���
	void AllOfTitle(QList<tuple<int, QString>> &titles);

	//����������
	//int,int,qstring : �£����⣬����
	void AllOfChapter(QList<tuple<int, int, QString>> &chapters);

	//���������û�
	void AllofUsr(QList<tuple<int, QString>> &usrs);

	//����ָ������Ŀsubject
	//chapterId���£�int,qstring,int,��Ŀid����������ֵ
	void SpecifySubject(const int chapterId, tuple<int,QString,int> &subject);

	/*�޸�....*/
	//�޸ı��������
	bool ModifyTitle(const int titleId, const QString &script);

	//�޸��µ�����
	bool ModifyChapter(const int chapterId, const QString &script);

	//�޸���Ŀ�����scoreû�б�ָ��ֵ��ΪĬ��ֵʱ�����޸�score��ֵ
	bool ModifySubject(const int subjectId, const QString &script, const int score = -1);

	//�û�����,����
	bool CreateAnswer(const int user, const int subject, const QString &answer);

	//�û�����,����
	bool ModifyAnswer(const int user, const int subject, const QString &answer);

	//��������
	bool CreateComment(const int answer, const int score, const QString &comment);

	//��������
	bool ModifyComment(const int answer, const pair<bool,int> &score, const pair<bool,QString> &comment);
protected:
	//������ȫ�������и����ã�
	void createTable();
private:
	static DBEngine *uniqueInstance;
	QMutex *mutex;
};

#endif // DBENGINE_H
