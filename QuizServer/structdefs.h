#ifndef structdefs_H__
#define structdefs_H__
#include <QString>
typedef struct tagChapterData{
	int id;				//�µ�Ψһ��ʶ��
	QString script;		//�µ�����
}ChapterData;

typedef struct tagSubjectData{
	int id;				//��Ŀ��Ψһ��ʶ��
	int fk_chapter;		//�����Ǹ�chapter
	QString script;		//��Ŀ����
	int score;			//��Ŀ�ķ�ֵ
}SubjectData;

typedef struct tagUserData{
	int sock;			//socket description
	int usrId;			//�û�id
	QString usrName;	//�û�����
}UserData;
#endif // structdefs_H__