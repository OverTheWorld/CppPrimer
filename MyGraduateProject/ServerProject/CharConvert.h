#include<windows.h>
#include<string>

using std::wstring;
using std::string;

const string wcTomt(const wstring& str);
const wstring mtTowc(const string& pStr);

enum netMessage
{
	NM_downloadFile = 0,
	NM_query = 1,
	NM_comment = 2,
	NM_downloadComment = 3,
	NM_login = 4,
	NM_register = 5,
	NM_queryID = 6,
	NM_END = 100
};
struct netProtocol
{
	unsigned message;
	int len;
	char szText[512];
};
struct CommentStruct
{
	int time;
	char szText[100];
};
struct userStruct
{
	char userName[30];
	char userPassword[30];
};