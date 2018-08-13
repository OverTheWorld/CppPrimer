#include "Folders.h"
#include<iostream>
#include<algorithm>
#include"Message.h"

Folders::Folders()
{
}


Folders::~Folders()
{
	for_each(messages.begin(), messages.end(), [&](Message *pMes){pMes->remFolders(*this); });
}

void Folders::addMsg(Message &mes)
{
	messages.insert(&mes);
}
void Folders::remMsg(Message &mes)
{
	messages.erase(&mes);
}
void Folders::Print()const
{
	for_each(messages.cbegin(), messages.cend(), [](const Message *mes){std::cout << mes->getString() << std::endl; });
	std::cout << std::endl;
}