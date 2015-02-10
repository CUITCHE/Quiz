#ifndef PACKET_H
#define PACKET_H
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>
#define setter(Type,variable, name) void set##name(const Type val){this->variable = val;}
#define getter(Type,variable,name) const Type get##name()const{return variable;}
#define get_setter(Type,variable, name)\
	setter(Type,variable, name)\
	getter(Type,variable,name)
//网络操作标识符
enum NetAction{
	//登陆
	Login,
	//发出卷子的请求
	TestRequest,
	//向服务器提交答案
	Commit,
	//消息确认
	Confirmation
};
class Packet
{
public:
	Packet(){}
	~Packet(){}
	get_setter(int, action, Action);
	virtual QVariant parse(){
		QVariantMap res;
		res.insert("action", action);
		return res;
	}
	virtual void parse(const QVariant &data){
		auto res = data.toMap();
		action = res["action"].toInt();
	}
private:
	int action;
};

#endif // PACKET_H
