#pragma once
#include<set>
class Message;
class Folders
{
public:
	Folders();
	~Folders();
	void addMsg(Message &mes);
	void remMsg(Message &mes);
	void Print()const;
private:
	std::set<Message*> messages;
};

