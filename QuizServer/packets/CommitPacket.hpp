#ifndef CommitPacket_H__
#define CommitPacket_H__

#include "../Quiz/packets/Packet.hpp"

class CommitPacket :public Packet
{
public:
	CommitPacket(){ setAction(NetAction::Commit); }
	~CommitPacket(){}
	get_setter(int, subjectNum, SubjectNum);
	get_setter(QString&, text, Text);
	get_setter(int, userId, UserId);
	void parse(const QVariant &data){
		Packet::parse(data);
		auto res = data.toMap();
		subjectNum = res["subjectNum"].toInt();
		text = res["text"].toString();
		userId = res["userId"].toInt();
	}
	QVariant parse(){
		QVariantMap com = Packet::parse().toMap();
		com.insert("subjectNum", subjectNum);
		com.insert("text", text);
		com.insert("userId", userId);
		return com;
	}
private:
	int subjectNum;
	int userId;
	QString text;
};
#endif // CommitPacket_H__
