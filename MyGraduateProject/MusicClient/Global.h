#include<winsock2.h>
#include<mysql.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<string>
#include<CommCtrl.h>
#include"DCameraClass.h"
#include"DInputClass.h"
#include"DObjectClass.h"
#include"DSkyClass.h"
#include"DTerrainClass.h"
#include"CharConvert.h"
#include"mciPlayer.h"
#include"runtimeError.h"
#include"ClientNetworkClass.h"
#include"DataBaseClass.h"
#include"DBulletComment.h"
#include"UIBaseClass.h"
#include"Button.h"
#include"ListBox.h"
#include"Slider.h"
#include"TextLineClass.h"
#include"StaticText.h"

using std::wstring;
using std::to_wstring;

#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 700
#define WINDOW_ALL_HEIGHT 650
#define WINDOW_ALL_WIDTH 1100
#define WINDOW_MOVE_WIDTH (WINDOW_WIDTH+15)
#define WINDOW_MOVE_HEIGHT (WINDOW_HEIGHT+40)
#define SAFE_DELETE(p) {if(p){delete (p);(p) = NULL;}}
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p) = NULL;}}
#define IDPLAY 1
#define IDLEFT 2
#define IDRIGHT 3
#define IDTEXTTIME 4
#define IDPLAYSLIDER 5
#define IDTIME 6
#define IDSTATE 9
#define IDC_VOLUMN 10
#define IDTEXTVOLUMN 12
#define IDLISTBOX 13
#define IDINPUT 14
#define IDSEARCHTEXT 15
#define IDSEARCHLISTBOX 16
#define IDLYRIC 17
#define IDINPUTBTN 18

//User defined Message
#define WM_LISTBOXCREATE (WM_USER+1)
#define WM_SEARCHTEXTBOXCREATE (WM_USER+2)
#define WM_SEARCHLISTBOXCREATE (WM_USER+3)
#define WM_SEARCHBUTTONCREATE (WM_USER+4)
#define WM_INPUTCREATE (WM_USER+5)

int g_ThisUserId;
