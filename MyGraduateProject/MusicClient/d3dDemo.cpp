#include"Global.h"
#include"resource.h"

LPDIRECT3DDEVICE9 g_pd3dDevice;
LPD3DXFONT g_pd3dFont;
DInputClass *g_pInput;
DCameraClass *g_pCamera;
DObjectClass *g_pObject;
DTerrainClass *g_pTerrain;
DSkyClass *g_pSky;
DBulletComment *g_pComment;
ClientNetworkClass clientNetWork;
TCHAR szChildName[] = TEXT("CHILD");
TCHAR szExtendName[] = TEXT("Extend");
TCHAR szChildUIName[] = TEXT("ChildUI");
TCHAR szLyricName[] = TEXT("Lyric");
TCHAR szSearchTextName[] = TEXT("SearchText");
HWND g_hwnd;
HWND g_hwndChildUI;
mciPlayer *g_pPlayer;
bool g_bCursorShow = true;
bool isLyricOut = false;
const float velocity = 10.0f;

HMENU g_hRightMenu;
WNDPROC g_SearchListBoxProc;

void SetSong();

// new UI in here

int ilength,iPos;
HWND g_hwndLyric;
bool g_isLyricOut;

Button *g_pPlayButton,*g_pNextSong,*g_pLastSong;
Button *g_pLyricButton, *g_pPlayRoundButton,*g_pCloseButton;
ListBox *g_pListBox, *g_pSearchListBox;
Slider *g_pPlayProcessSlider, *g_pVolumnSlider;
TextLineClass *g_pTextSearch, *g_pTextComment;
StaticText *g_pTimeText, *g_pVolumnText;
HBITMAP g_hFireBitmap,g_hPlayPauseBitmap;
HBITMAP g_hSingleBitmap, g_hListBitmap, g_hRandBitmap;

void CloseBtn(Button* pThis, POINT pt, WPARAM wParam)
{
	SendMessage((HWND)GetWindowLongPtr(pThis->GetHwnd(),GWLP_HWNDPARENT), WM_CLOSE, 0, 0);
}
void PlayBtn(Button* pThis, POINT pt, WPARAM wParam)
{
	if (g_pPlayer->getState() == pause)
	{
		g_pPlayer->Play();
		g_hPlayPauseBitmap = pThis->SetBackBitmap(g_hPlayPauseBitmap);
	}
	else if (g_pPlayer->getState() == playing)
	{
		g_pPlayer->Pause();
		g_hPlayPauseBitmap = pThis->SetBackBitmap(g_hPlayPauseBitmap);
	}
	else if (g_pPlayer->getState() == Stoped)
	{
		g_pPlayer->Play();
		if (g_pPlayer->getState() != Stoped)
		{
			g_hPlayPauseBitmap = pThis->SetBackBitmap(g_hPlayPauseBitmap);
			SetSong();
			g_pListBox->SetPlayingItem(0);
		}
	}
}
void LeftBtn(Button* pThis, POINT pt, WPARAM wParam)
{
	auto iState = g_pPlayer->getState();
	if (iState == Stoped)
		return;
	g_pPlayer->lastSong();
	SetSong();
	int index;
	if (g_pListBox->GetPlayingItemIndex() - 1 == -1)
	{
		index = g_pPlayer->getList().size() - 1;
	}
	else
	{
		index = g_pListBox->GetPlayingItemIndex() - 1;
	}
	g_pListBox->SetPlayingItem(index);
	if (iState != g_pPlayer->getState())
		g_hPlayPauseBitmap = g_pPlayButton->SetBackBitmap(g_hPlayPauseBitmap);
}
void RightBtn(Button* pThis, POINT pt, WPARAM wParam)
{
	auto iState = g_pPlayer->getState();
	if (iState == Stoped)
		return;
	g_pPlayer->nextSong();
	SetSong();
	auto NowMusicFile = g_pPlayer->getCurMusicFile();
	int index = 0;
	for (auto iter = g_pPlayer->getList().begin(); iter != g_pPlayer->getList().end(); ++iter,++index)
	{
		if (iter->getStrFileName() == NowMusicFile.getStrFileName())break;
	}
	g_pListBox->SetPlayingItem(index);
	if (iState != g_pPlayer->getState())
		g_hPlayPauseBitmap = g_pPlayButton->SetBackBitmap(g_hPlayPauseBitmap);
}
void PlayStateBtn(Button* pThis, POINT pt, WPARAM wParam)
{
	if (g_pPlayer->getPlayState() == playSingle)
	{
		g_pPlayer->setPlayState(playRound);
		pThis->SetBackBitmap(g_hListBitmap);
		//process some operation
	}
	else if (g_pPlayer->getPlayState() == playRound)
	{
		g_pPlayer->setPlayState(playRand);
		pThis->SetBackBitmap(g_hRandBitmap);
		//process some operation
	}
	else
	{
		g_pPlayer->setPlayState(playSingle);
		pThis->SetBackBitmap(g_hSingleBitmap);
	}
}
void ListBoxDoubleClick(UIBaseClass* pBase, int index, wstring str)
{
	auto iState = g_pPlayer->getState();
	g_pPlayer->SetCurMusicFile(index);
	SetSong();
	if (iState != g_pPlayer->getState())
		g_hPlayPauseBitmap = g_pPlayButton->SetBackBitmap(g_hPlayPauseBitmap);
}
void LyricBtn(Button* pThis, POINT pt, WPARAM wParam)
{
	g_isLyricOut = !g_isLyricOut;
	if (g_isLyricOut)
	{
		g_hwndLyric = CreateWindowEx(
			0, szLyricName, NULL, WS_POPUP | WS_MINIMIZEBOX, 200, 600, 800, 100,
			g_hwnd, NULL, (HINSTANCE)GetWindowLong(g_hwnd, GWLP_HINSTANCE), NULL
			);
		ShowWindow(g_hwndLyric, SW_NORMAL);
	}
	else
	{
		SendMessage(g_hwndLyric, WM_CLOSE, 0, 0);
	}
}
void CommentInput(UIBaseClass* pBaseClass, const wstring &strInputText)
{
	TextLineClass *pTextLine = (TextLineClass*)pBaseClass;
	if (!g_pPlayer->getList().empty()&&g_pPlayer->getState() != Stoped)
	{
		CommentClass cc;
		cc.strComment = strInputText;
		cc.time = g_pPlayer->getCurrentPos() / 1000;
		g_pComment->GetComment(cc);
		clientNetWork.SendComment(strInputText, g_pPlayer->getCurrentPos() / 1000 + 2, g_pPlayer->getCurMusicFile().getSID());
	}
	pTextLine->SetInputStr(L"");
	SetFocus((HWND)GetWindowLongPtr(pTextLine->GetHwnd(),GWLP_HWNDPARENT));
}
void PlaySlider(int pos)
{
	g_pPlayer->MoveTo((unsigned)pos);
}
void VolumnSlider(int pos)
{
	g_pPlayer->setVolumn((unsigned)pos);
	g_pVolumnText->SetText(to_wstring(pos));
}
void SongListBoxCreateSeting()
{
	const auto listMusicFile = g_pPlayer->getList();
	for (const auto &s : listMusicFile)
	{
		g_pListBox->AddItem(s.getStrFileName());
	}
}
void ListBoxMenu(UIBaseClass* pBase, int index, wstring str, int iId)
{
	ListBox* pList = (ListBox*)pBase;
	switch (iId)
	{
	case ID_RAdd:
		if (g_pPlayer->addMusic())
		{
			pList->AddItem(g_pPlayer->getList().back().getStrFileName());
		}
		break;
	case ID_RDelete:
		if (index == -1)
			return;
		pList->DeleteItem(index);
		if (g_pPlayer->getCurMusicFile().getStrFileName() == str)
		{
			auto iState = g_pPlayer->getState();
			g_pPlayer->deleteMusic(g_pPlayer->getCurMusicFile().getStrFileName());
			if (iState != g_pPlayer->getState()&&(iState != pause&&g_pPlayer->getState() == Stoped))
				g_hPlayPauseBitmap = g_pPlayButton->SetBackBitmap(g_hPlayPauseBitmap);
			SetSong();
		}
		else
		{
			g_pPlayer->deleteMusic(str);
		}
		break;
	case ID_RPlay:
		if (index == -1)
			return;
		auto iState = g_pPlayer->getState();
		g_pPlayer->SetCurMusicFile(index);
		pList->SetPlayingItem(index);
		if (iState != g_pPlayer->getState())
			g_hPlayPauseBitmap = g_pPlayButton->SetBackBitmap(g_hPlayPauseBitmap);
		break;
	}
}
void SearchListBoxDoubleClick(UIBaseClass* pBase, int index, wstring str)
{
	ListBox* pList = (ListBox*)pBase;
	clientNetWork.GetFile(str.c_str());
	MusicFile mf(clientNetWork.getStrSaveSite() + str + L".mp3", str);
	mf.SetSID(clientNetWork.queryID(str));
	mf.SetSiteLyricName(str);
	mf.SetStrLyricSite(clientNetWork.getStrSaveSite() + str + L".lyric");
	if (g_pDataBaseClass->insertData(mf))
	{
		auto iState = g_pPlayer->getState();
		g_pPlayer->getList().push_back(mf);
		g_pPlayer->SetCurMusicFile(--g_pPlayer->getList().end());
		g_pListBox->AddItem(str);
		g_pListBox->SetPlayingItem(g_pPlayer->getList().size() - 1);
		SetSong();
		if (iState != g_pPlayer->getState())
			g_hPlayPauseBitmap = g_pPlayButton->SetBackBitmap(g_hPlayPauseBitmap);
	}
	g_pSearchListBox->SetShow(false);
	g_pListBox->SetShow(true);
}
void GetInputString(UIBaseClass* pBase, const wstring& str)
{
	vector<wstring> vecStr;
	
	g_pSearchListBox->ClearItem();
	clientNetWork.vagueQuery(str, vecStr);
	for (const auto &s : vecStr)
	{
		g_pSearchListBox->AddItem(s);
	}
	g_pSearchListBox->SetShow(true);
	g_pListBox->SetShow(false);
}
//End

D3DDISPLAYMODE d3ddisplayMode;
HRESULT Direct3D_Init(HWND hwnd);
HRESULT Objects_Init(HWND hwnd);
void Lighting_set();
void Direct3D_Update(HWND hwnd);
void Direct3D_Render(HWND hwnd);
void Direct3D_CleanUp();
float getFPS();

void InitCheck(HINSTANCE hInst);

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LyricProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DialogLoginProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DialogRegisterProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int iCmdShow
	)
{

	//验证程序

	InitCheck(hInstance);

	HWND hwnd;
	WNDCLASSEX wndClass;
	TCHAR szAppName[] = TEXT("D3DDemo");
	MSG msg = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.style = 0;
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;

	if (!RegisterClassEx(&wndClass))
	{
		MessageBox(NULL, TEXT("Fail to RegisterClass!"), TEXT("ERROR"), 0 | MB_ICONERROR);
		return -1;
	}

	wndClass.lpfnWndProc = ChildProc;
	wndClass.lpszClassName = szChildName;

	if (!RegisterClassEx(&wndClass))
	{
		MessageBox(NULL, TEXT("Fail to RegisterClass!"), TEXT("ERROR"), 0 | MB_ICONERROR);
		return -1;
	}

	wndClass.lpfnWndProc = LyricProc;
	wndClass.lpszClassName = szLyricName;

	if (!RegisterClassEx(&wndClass))
	{
		MessageBox(NULL, TEXT("Fail to RegisterClass!"), TEXT("ERROR"), 0 | MB_ICONERROR);
		return -1;
	}

	g_hRightMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_RBMENU));

	Init(hInstance);

	hwnd = CreateWindowEx(
		0, szAppName, TEXT("d3dDemo Window"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_ALL_WIDTH, WINDOW_ALL_HEIGHT,
		NULL, NULL, hInstance, NULL
		);
	if (FAILED(Direct3D_Init(g_hwnd)))
	{
		MessageBox(NULL, TEXT("Fail to Direct3D Init!"), TEXT("ERROR"), 0 | MB_ICONERROR);
		return -1;
	}
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	ShowWindow(g_hwnd, SW_NORMAL);
	ShowWindow(g_hwndChildUI, SW_NORMAL);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Direct3D_Update(g_hwnd);
			Direct3D_Render(g_hwnd);
		}
	}
	DestroyMenu(g_hRightMenu);
	UnregisterClass(szAppName, hInstance);
	return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	static HMENU hListRightMenu,hSearchListRightMenu;
	static HINSTANCE hInstance;
	static HRGN hRgn;
	static HMENU hMenuListBox,hMenuSearchListBox;
	wstring strTime, strVolumn;
	wchar_t szText[100];
	HDC hdc, hdcSrc;
	RECT rect;
	PAINTSTRUCT ps;
	POINT pt;
	switch (message)
	{
	case WM_CREATE:
		//DataBase Class Init
		g_pDataBaseClass = new DataBaseClass(g_ThisUserId);
		g_pPlayer = new mciPlayer(hwnd);
		g_hFireBitmap = (HBITMAP)LoadImage(NULL, L"FireGauss.bmp", 0, WINDOW_ALL_WIDTH, WINDOW_ALL_HEIGHT, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hListBitmap = (HBITMAP)LoadImage(NULL, L"ListRound.bmp", 0, 50, 50, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_hRandBitmap = (HBITMAP)LoadImage(NULL, L"RandRound.bmp", 0, 50, 50, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		hMenuListBox = GetSubMenu(g_hRightMenu, 0);
		hMenuSearchListBox = GetSubMenu(g_hRightMenu, 1);
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		//Get Menu
		hListRightMenu = GetSubMenu(g_hRightMenu, 0);
		hSearchListRightMenu = GetSubMenu(g_hRightMenu, 1);
		//the DirectWindow Show
		g_hwnd = CreateWindowEx(
			0, szChildName, TEXT("d3dDemo Window"), WS_CHILD|WS_BORDER,
			190, 40, WINDOW_WIDTH, WINDOW_HEIGHT,
			hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL
			);
		ShowWindow(g_hwnd, SW_NORMAL);

		//UI Seting and Create

		//Window Seting
		pt.x = 0;
		pt.y = 0;
		SetRect(&rect, 0, 0, WINDOW_ALL_WIDTH, WINDOW_ALL_HEIGHT);
		hRgn = CreateRoundRectRgn(rect.left + 20, rect.top + 30, rect.right - 20, rect.bottom - 20, 50, 50);
		SetWindowRgn(hwnd, hRgn, true);

		//LastSongButton Create and Seting
		SetRect(&rect, 30, 540, 50, 50);
		g_pLastSong = new Button(hwnd, rect, enRound, L"Left.bmp", enRightAngle, pt, g_hFireBitmap);
		g_pLastSong->SetLeftMouseButtonUpFunc(LeftBtn);

		//Playing Button Create and Seting
		SetRect(&rect, 90, 530, 70, 70);
		g_pPlayButton = new Button(hwnd, rect, enRound, L"Playing.bmp", enRightAngle, pt, g_hFireBitmap);
		g_hPlayPauseBitmap = (HBITMAP)LoadImage(NULL, L"Pause.bmp", 0, rect.right, rect.bottom, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		g_pPlayButton->SetLeftMouseButtonUpFunc(PlayBtn);

		//nextSongButton Create and Seting
		SetRect(&rect, 170, 540, 50, 50);
		g_pNextSong = new Button(hwnd, rect, enRound, L"Right.bmp", enRightAngle, pt, g_hFireBitmap);
		g_pNextSong->SetLeftMouseButtonUpFunc(RightBtn);

		//playSlider Create and Seting
		SetRect(&rect, 240, 560, 500, 10);
		g_pPlayProcessSlider = new Slider(hwnd, rect, RGB(0XE6, 0XE6, 0XE8), RGB(0XE8, 0X3C, 0X3C), g_pPlayer->getlength()/1000, enHorizon, g_hFireBitmap);
		g_pPlayProcessSlider->SetSliderProc(PlaySlider);

		//PlayTime Text Create and Seting
		SetRect(&rect, 750, 560, 100, 50);
		ilength = (int)g_pPlayer->getlength() / 1000;
		wsprintf(szText, TEXT("00:00/%2u:%2u"), ilength / 60, ilength % 60);
		g_pTimeText = new StaticText(hwnd, rect, g_hFireBitmap, szText);

		//Volumn Slider Create and Seting
		SetRect(&rect, 30, 380, 10, 100);
		g_pVolumnSlider = new Slider(hwnd, rect, RGB(0XE6, 0XE6, 0XE8), RGB(0XE8, 0X3C, 0X3C), g_pPlayer->getVolumn(), enVertical, g_hFireBitmap);
		g_pVolumnSlider->SetSliderProc(VolumnSlider);
		g_pVolumnSlider->SetPos(100);

		//Volumn Text Create and Seting
		SetRect(&rect,0, 480, 70, 50);
		g_pVolumnText = new StaticText(hwnd, rect, g_hFireBitmap, L"100");

		//LyricButton Create and Seting
		SetRect(&rect, 100, 400, 50, 50);
		g_pLyricButton = new Button(hwnd, rect, enRound, L"", enRightAngle, pt, g_hFireBitmap);
		g_pLyricButton->SetText(L"词");
		g_pLyricButton->SetLeftMouseButtonUpFunc(LyricBtn);

		//PlayStateButton Create and Seting
		SetRect(&rect, 100, 470, 50, 50);
		g_pPlayRoundButton = new Button(hwnd, rect, enRound, L"SingleRound1.bmp", enRightAngle, pt, g_hFireBitmap);
		g_hSingleBitmap = g_pPlayRoundButton->GetBackBitmap();
		g_pPlayRoundButton->SetLeftMouseButtonUpFunc(PlayStateBtn);

		//ListBox Create and Seting
		SetRect(&rect, 910, 100, 150, 400);
		pt.x = 50;
		pt.y = 50;
		g_pListBox = new ListBox(hwnd, rect, enObtuseAngle, pt, L"歌曲列表", hMenuListBox, g_hFireBitmap);
		SongListBoxCreateSeting();
		g_pListBox->SetPlayingProc(ListBoxDoubleClick);
		g_pListBox->SetSelectMenuProc(ListBoxMenu);

		//SearchText Create and Seting
		SetRect(&rect, 910, 20, 150, 50);
		g_pTextSearch = new TextLineClass(hwnd, rect, g_hFireBitmap, true);
		g_pTextSearch->SetInputFunc(GetInputString);

		//SearchListBox Create and Seting
		SetRect(&rect, 910, 70, 150, 400);
		g_pSearchListBox = new ListBox(hwnd, rect, enObtuseAngle, pt, L"结果如下：", hMenuSearchListBox, g_hFireBitmap);
		g_pSearchListBox->SetShow(false);
		g_pSearchListBox->SetPlayingProc(SearchListBoxDoubleClick);

		//Comment TextLine Create and Seting
		SetRect(&rect, 910, 500, 150, 50);
		g_pTextComment = new TextLineClass(hwnd, rect, g_hFireBitmap, false);
		g_pTextComment->SetInputFunc(CommentInput);

		//CloseButton Create and Seting
		SetRect(&rect, 20, 0, 50, 50);
		g_pCloseButton = new Button(hwnd, rect, enRound, L"CloseButton.bmp", enRightAngle, pt, g_hFireBitmap);
		g_pCloseButton->SetLeftMouseButtonUpFunc(CloseBtn);
		//Set Timer 
		SetTimer(hwnd, IDTIME, 1000, NULL);

		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rect);
		hdc = BeginPaint(hwnd, &ps);
		hdcSrc = CreateCompatibleDC(hdc);
		SelectObject(hdcSrc, g_hFireBitmap);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcSrc, 0, 0, SRCCOPY);
		DeleteDC(hdcSrc);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		if (g_pPlayer->getState() == playing)
		{
			iPos = (int)g_pPlayer->getCurrentPos() / 1000;
			g_pPlayProcessSlider->SetPos(iPos);
			wsprintf(szText, TEXT("%02u:%02u/%02u:%02u"), iPos / 60, iPos % 60, ilength / 60, ilength % 60);
			g_pTimeText->SetText(szText);
		}
		break;
	case WM_NCHITTEST:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		ScreenToClient(hwnd, &pt);
		if (pt.y < 15 && pt.x < WINDOW_ALL_WIDTH - 200)
			return HTCAPTION;
		else
			return HTCLIENT;
		break;
	case MM_MCINOTIFY:
		g_pPlayer->ProcessingNotify(wParam, lParam);
		if (wParam == MCI_NOTIFY_SUCCESSFUL)
		{
			SetSong();

			auto NowMusicFile = g_pPlayer->getCurMusicFile();
			int index = 0;
			for (auto iter = g_pPlayer->getList().begin(); iter != g_pPlayer->getList().end(); ++iter, ++index)
			{
				if (iter->getStrFileName() == NowMusicFile.getStrFileName())break;
			}
			g_pListBox->SetPlayingItem(index);
		}
		break;
	case WM_DESTROY:
		KillTimer(hwnd, IDTIME);
		DeleteObject(g_hPlayPauseBitmap);
		DeleteObject(g_hFireBitmap);
		delete g_pPlayer;
		delete g_pDataBaseClass;
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK ChildProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HRGN hRgn;
	RECT rect;
	switch (message)
	{
	case WM_PAINT:
		GetClientRect(hwnd, &rect);
		hRgn = CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, 40, 40);
		SetWindowRgn(hwnd, hRgn, true);
		Direct3D_Render(hwnd);
		ValidateRect(hwnd, NULL);
		break;

	case WM_LBUTTONDOWN:
		SetFocus(hwnd);
		break;
	case WM_SETFOCUS:
		if (g_bCursorShow)
		{
			g_bCursorShow = false;
			ShowCursor(false);
		}
		break;
	case WM_DESTROY:
		Direct3D_CleanUp();
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
HRESULT Direct3D_Init(HWND hwnd)
{
	LPDIRECT3D9 pd3d = NULL;
	if (NULL == (pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}
	int vp = 0;
	D3DCAPS9 caps;
	if (FAILED(pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	pd3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddisplayMode);
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = d3ddisplayMode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;

	if (FAILED(pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pd3d);

	g_pInput = new DInputClass(hwnd);
	g_pCamera = new DCameraClass(g_pd3dDevice,D3DXVECTOR3(0,4500,0),70000.0f);

	return Objects_Init(hwnd);
}
HRESULT Objects_Init(HWND hwnd)
{
	srand(timeGetTime());
	if (FAILED(D3DXCreateFontW(g_pd3dDevice, 25, 0, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("微软雅黑"), &g_pd3dFont)))
	{
		return E_FAIL;
	}

	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;;
	light.Ambient = D3DXCOLOR(1, 1, 1, 1);
	light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	light.Specular = D3DXCOLOR(1, 1, 1, 1);
	light.Direction = D3DXVECTOR3(1, 0, 1);
	light.Attenuation0 = 1;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;
	light.Position = D3DXVECTOR3(0, 200, 0);
	light.Range = 700;
	g_pd3dDevice->SetLight(0, &light);
	g_pd3dDevice->LightEnable(0, true);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pd3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	g_pTerrain = new DTerrainClass(L"heighmap.raw", L"terrainstone.jpg", g_pd3dDevice, 200, 200, 300, 20);
	//g_pSky = new DSkyClass(g_pd3dDevice, L"leftsnow1.jpg", L"rightsnow1.jpg", L"topsnow1.jpg", L"frontsnow1.jpg", L"backsnow1.jpg", 70000);
	g_pSky = new DSkyClass(g_pd3dDevice, L"LF.tga", L"RT.tga", L"UP.tga", L"FR.tga", L"BK.tga", 70000);
	g_pComment = new DBulletComment(g_pd3dDevice, 30, d3ddisplayMode.Format);
	g_pComment->Init();

	return S_OK;
}
void Direct3D_Update(HWND hwnd)
{
	if (!g_bCursorShow)
	{
		g_pInput->KeyboardAcquire();
		g_pInput->MouseAcquire();
		float x = 0, y = 0, z = 0;
		float rx = 0, ry = 0;
		if (g_pInput->isKeyDown(DIK_A))
		{
			x = -velocity;
		}
		if (g_pInput->isKeyDown(DIK_D))
		{
			x = velocity;
		}
		if (g_pInput->isKeyDown(DIK_W))
		{
			z = velocity;
		}
		if (g_pInput->isKeyDown(DIK_S))
		{
			z = -velocity;
		}
		if (g_pInput->isKeyDown(DIK_UP))
		{
			y = velocity;
		}
		if (g_pInput->isKeyDown(DIK_DOWN))
		{
			y = -velocity;
		}

		if (g_pInput->isKeyDown(DIK_ESCAPE))
		{
			if (!g_bCursorShow)
			{
				g_bCursorShow = true;
				ShowCursor(true);
			}
		}

		long lx, ly, lz;
		g_pInput->getMouseMove(lx, ly, lz);
		rx = lx * 0.01f;
		ry = ly * 0.01f;
		g_pCamera->SetMoveX(x);
		g_pCamera->SetMoveY(y);
		g_pCamera->SetMoveZ(z);
		g_pCamera->rotationX(ry);
		g_pCamera->rotationY(rx);
		g_pCamera->SetViewTransform();
	}
	static float fcurrentTime, flastTime;
	fcurrentTime = timeGetTime()*0.001f;
	float DeltaTime = fcurrentTime - flastTime;
	flastTime = fcurrentTime;
	g_pComment->Update(DeltaTime, (g_pPlayer == NULL || g_pPlayer->getState() == Stoped) ? 0:(g_pPlayer->getCurrentPos()/1000));
}
void Direct3D_Render(HWND hwnd)
{
	static int iCount = 0;
	++iCount;
	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&matWorld, 0, -500, 0);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	RECT rect;
	SetRect(&rect, 0, 0, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10);

	GetClientRect(hwnd, &rect);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(50, 100, 250), 1.0f, 0);
	g_pd3dDevice->BeginScene();

	wstring str(to_wstring(getFPS()));
	g_pd3dFont->DrawText(NULL, str.c_str(), str.size(), &rect, DT_TOP | DT_RIGHT, D3DCOLOR_XRGB(255, 0, 255));
	g_pd3dFont->DrawTextW(NULL, g_pPlayer->getNowLyric().c_str(), g_pPlayer->getNowLyric().size(), &rect, DT_BOTTOM | DT_CENTER, D3DCOLOR_XRGB(255, 0, 255));

	g_pComment->Render();

	g_pTerrain->DrawTerrain(false);
	D3DXMatrixTranslation(&matWorld, 0, 5000, 0);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pSky->DrawSkyBox(NULL);
	

	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
void Direct3D_CleanUp()
{

	SAFE_DELETE(g_pComment);

	SAFE_DELETE(g_pInput);
	SAFE_DELETE(g_pCamera);
	SAFE_DELETE(g_pObject);
	SAFE_DELETE(g_pSky);
	SAFE_DELETE(g_pTerrain);
	SAFE_RELEASE(g_pd3dFont);
	SAFE_RELEASE(g_pd3dDevice);
}
float getFPS()
{
	static float fps, lasttime, currenttime;
	static unsigned uCount;
	++uCount;
	currenttime = timeGetTime()*0.001f;
	while (currenttime - lasttime > 1.0f)
	{
		fps = static_cast<float>(uCount) / (currenttime - lasttime);
		lasttime = currenttime;
		uCount = 0;
	}
	return fps;
}
void InitCheck(HINSTANCE hInst)
{
	if (DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN), NULL, DialogLoginProc) == 0)
	{
		exit(0);
	}
}
INT_PTR CALLBACK DialogLoginProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	wstring strUserName, strPassword;
	wchar_t szText[100];
	int result;
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		//控件消息
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hwnd, IDC_USERNAME, szText, 100);
			strUserName = szText;
			if (strUserName.size() == 0)
			{
				MessageBox(hwnd, L"userName couldn't be null!", L"ERROR", 0 | MB_ICONERROR);
				break;
			}
			GetDlgItemText(hwnd, IDC_USERPASSWORD, szText, 100);
			strPassword = szText;
			if (strPassword.size() == 0)
			{
				MessageBox(hwnd, L"Password couldn't be null!", L"ERROR", 0 | MB_ICONERROR);
				break;
			}
			result = clientNetWork.userLogin(strUserName, strPassword, g_ThisUserId);
			if (result == 1)
			{
				EndDialog(hwnd, 1);
			}
			else if (result == 0)
			{
				MessageBox(hwnd, L"password wrong", L"Error", 0 | MB_ICONERROR);
				break;
			}
			else if (result == -1)
			{
				MessageBox(hwnd, L"user does not exist!", L"Error", 0 | MB_ICONERROR);
				break;
			}
			else
			{
				MessageBox(hwnd, L"Unknown Error", L"Error", 0 | MB_ICONERROR);
				break;
			}
			break;
		case IDROK:
			DialogBox((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDD_REGISTER), hwnd, DialogRegisterProc);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);//结束Dialog
			return TRUE;
			//结束
		}
		break;
	}
	return FALSE;
}
INT_PTR CALLBACK DialogRegisterProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	wstring strPassword, strPasswordOk, strUserName;
	wchar_t szText[100];
	switch (message)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hwnd, IDC_RUSERNAME, szText, 100);
			strUserName = szText;
			if (strUserName.size() == 0)
			{
				MessageBox(hwnd, L"userName couldn't be null!", L"ERROR", 0 | MB_ICONERROR);
				break;
			}
			GetDlgItemText(hwnd, IDC_RPASSWORD, szText, 100);
			strPassword = szText;
			if (strPassword.size() == 0)
			{
				MessageBox(hwnd, L"Password couldn't be null!", L"ERROR", 0 | MB_ICONERROR);
				break;
			}
			GetDlgItemText(hwnd, IDC_RPASSWORDAGAIN, szText, 100);
			strPasswordOk = szText;
			if (strPassword != strPasswordOk)
			{
				MessageBox(hwnd, L"your password do not match!", L"ERROR", 0 | MB_ICONERROR);
			}
			else
			{
				if (clientNetWork.userRegister(strUserName, strPassword))
				{
					EndDialog(hwnd, 0);
				}
				else
				{
					MessageBox(hwnd, L"userName has existed!", 0, 0);
				}
			}
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return false;
}
void SetSong()
{
	wstring strMusicInfo;
	wchar_t szText[100];
	ilength = (int)g_pPlayer->getlength()/1000;
	g_pPlayProcessSlider->SetLength(ilength);
	wsprintf(szText, TEXT("00:00/%02u:%02u"), ilength / 60, ilength % 60);
	g_pTimeText->SetText(szText);
	if (g_pPlayer->getList().empty())
	{
		strMusicInfo = L"";
	}
	else
	{
		strMusicInfo = g_pPlayer->getCurMusicFile().getStrFileName();
		clientNetWork.GetComments(g_pPlayer->listComment, g_pPlayer->getCurMusicFile().getSID());
		g_pComment->SetCommentList(g_pPlayer->listComment.empty() ? NULL : (&g_pPlayer->listComment));
	}
	SetWindowText(g_hwnd, strMusicInfo.c_str());
}
LRESULT CALLBACK LyricProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	const static int IDTIMELYRIC = 100;
	static HFONT hFont;
	long lStyle;
	BLENDFUNCTION bf;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (message)
	{
	case WM_CREATE:
		hFont = CreateFont(50, 30, 0, 0, FW_THIN, true, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, 0, L"微软雅黑");
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 255;
		lStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
		SetWindowLong(hwnd, GWL_EXSTYLE, lStyle^WS_EX_LAYERED);
		SetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
		SetTimer(hwnd,IDTIMELYRIC, 100, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, hFont);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, g_pPlayer->getNowLyric().c_str(), g_pPlayer->getNowLyric().size(), &rect, DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		InvalidateRect(hwnd, NULL, true);
		break;
	case WM_NCHITTEST:
		return HTCAPTION;
	case WM_CLOSE:
		KillTimer(hwnd, IDTIMELYRIC);
		DeleteObject(hFont);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
