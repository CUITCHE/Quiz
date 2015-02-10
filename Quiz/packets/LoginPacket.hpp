#ifndef LoginPacket_H__
#define LoginPacket_H__

#include "../Quiz/packets/Packet.hpp"

class LoginPacket : public Packet
{
public:
	LoginPacket() :userId(0){ setAction(NetAction::Login); }
	~LoginPacket(){}
	get_setter(QString&, name, Name);
	get_setter(QString&, loginCode, LoginCode);
	get_setter(int, userId, UserId);
	void parse(const QVariant &data){
		Packet::parse(data);
		auto res = data.toMap();
		name = res["name"].toString();
		loginCode = res["loginCode"].toString();
		userId = res["userId"].toInt();
	}
	QVariant parse(){
		QVariantMap man = Packet::parse().toMap();
		man.insert("name", name);
		man.insert("loginCode", loginCode);
		man.insert("userId", userId);
		return man;
	}
private:
	QString name;
	QString loginCode;
	int userId;		//���������������½�ɹ������᷵�ط�0ֵ����ΪΨһ��ʶ��
};
#endif // LoginPacket_H__
