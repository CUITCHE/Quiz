#ifndef structdefs_H__
#define structdefs_H__
#include <QString>
typedef struct tagChapterData{
	int id;				//章的唯一标识符
	QString script;		//章的描述
}ChapterData;

typedef struct tagSubjectData{
	int id;				//题目的唯一标识符
	int fk_chapter;		//属于那个chapter
	QString script;		//题目描述
	int score;			//题目的分值
}SubjectData;

typedef struct tagUserData{
	int sock;			//socket description
	int usrId;			//用户id
	QString usrName;	//用户名字
}UserData;
#endif // structdefs_H__
