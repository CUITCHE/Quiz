#ifndef ConfirmationPacket_H__
#define ConfirmationPacket_H__

#include "../Quiz/packets/Packet.hpp"

class ConfirmationPacket :public Packet
{
public:
	ConfirmationPacket(){ setAction(NetAction::Confirmation); }
	~ConfirmationPacket(){}
	get_setter(int, whichAction, WhichAction);
	get_setter(int, other, Other);
	void parse(const QVariant &data){
		Packet::parse(data);
		auto res = data.toMap();
		whichAction = res["whichAction"].toInt();
		other = res["other"].toInt();
	}

	QVariant parse(){
		QVariantMap res = Packet::parse().toMap();
		res.insert("whichAction", whichAction);
		res.insert("other", other);
		return res;
	}
private:
	int whichAction;
	int other;		//0³É¹¦£¬1Ê§°Ü£¬2½ûÖ¹µÇÂ½
};
#endif // ConfirmationPacket_H__
