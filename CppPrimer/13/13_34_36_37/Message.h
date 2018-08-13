#pragma once
#include<string>
#include<set>
class Message
{
	friend class Folders;
public:
	Message(const std::string &str = "");
	Message(const Message &mes);
	~Message();
	Message& operator=(Message& mes);
	void addFolders(Folders &f);
	void remFolders(Folders &f);
	std::string getString()const{ return strContent; }
private:
	std::string strContent;
	std::set<Folders*> folders;
	void remove_all_folders();
	void add_to_folders(const Message &mes);
};

