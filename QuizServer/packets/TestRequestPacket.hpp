#ifndef TestRequestPacket_H__
#define TestRequestPacket_H__
#include "../Quiz/packets/Packet.hpp"
class TestRequestPacket : public Packet
{
public:
	TestRequestPacket(){ setAction(NetAction::TestRequest); }
	~TestRequestPacket(){}
	get_setter(QString&, title, Title);
	get_setter(QJsonArray&, chapter, Chapter);
	get_setter(QJsonArray&, subject, Subject);
	void parse(const QVariant &data){
		Packet::parse(data);
		auto res = data.toMap();
		title = res["title"].toString();
		chapter = QJsonArray::fromVariantList(res["chapters"].toList());
		subject = QJsonArray::fromVariantList(res["subjects"].toList());
	}
	QVariant parse(){
		QVariantMap test = Packet::parse().toMap();
		test.insert("title", title);
		test.insert("chapters", chapter);
		test.insert("subjects", subject);
		return test;
	}
private:
	QString title;
	QJsonArray chapter;	//id,script
	QJsonArray subject;	//id,fk_chapter,script,score;
};
#endif // TestRequestPacket_H__
