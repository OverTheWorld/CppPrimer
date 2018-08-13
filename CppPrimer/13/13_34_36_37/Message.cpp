#include "Message.h"
#include<algorithm>
#include<iostream>
#include"Folders.h"
Message::Message(const std::string &str):
strContent(str)
{

}

Message::Message(const Message &mes):
strContent(mes.strContent), folders(mes.folders)
{
	add_to_folders(mes);
}

Message::~Message()
{
	remove_all_folders();
}

Message& Message::operator=(Message& mes)
{
	remove_all_folders();
	strContent = mes.strContent;
	folders = mes.folders;
	add_to_folders(mes);
	return *this;
}
void Message::addFolders(Folders &f)
{
	folders.insert(&f);
	f.addMsg(*this);
}
void Message::remFolders(Folders &f)
{
	folders.erase(&f);
	f.remMsg(*this);
}
void Message::remove_all_folders()
{
	for_each(folders.begin(), folders.end(), [this](Folders *pFolder){pFolder->remMsg(*this); });
}
void Message::add_to_folders(const Message &mes)
{
	for_each(mes.folders.begin(), mes.folders.end(), [this](Folders* pFolders){pFolders->addMsg(*this); });
	std::cout << std::endl;
}