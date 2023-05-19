#pragma once

typedef LRESULT(*FXN)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#define dim(x) (sizeof(x) / sizeof(x[0]))

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{

	return 0;
}

//MiniWnd class

class MiniWnd
{
public:
	bool Create();
	bool ShowWindow();
	bool UpdateWindow();
	HWND m_hWnd;

	static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	MINI_MESSAGE_DECLARE()

	struct tagMESSAGEMAP {
		UINT uMsg;
		FXN pFun;
	};

	const static tagMESSAGEMAP MessageMaps[];
};


MINI_MESSAGE_MAP()

LRESULT CALLBACK MiniWnd::WinProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	for (int i = 0; i < dim(MessageMaps); i++) {
		if (uMsg == MessageMaps[i].uMsg) {
			FXN fun = MessageMaps[i].pFun;
			return fun(hWnd, uMsg, wParam, lParam);
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool MiniWnd::Create()
{
	// TODO: Add your implementation code here.
	//1.
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = NULL;
	wndcls.lpfnWndProc = MiniWnd::WinProc;
	wndcls.lpszClassName = TEXT("win32ToMFC");
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	//2.
	m_hWnd = CreateWindow(
		wndcls.lpszClassName,
		TEXT("caption"),
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		600,
		400,
		NULL,
		NULL,
		NULL,
		NULL
	);

	return (m_hWnd != NULL);
}

bool MiniWnd::ShowWindow()
{
	// TODO: Add your implementation code here.
	//3.
	return ::ShowWindow(m_hWnd, SW_SHOWNORMAL);
}


bool MiniWnd::UpdateWindow()
{
	// TODO: Add your implementation code here.
	//4.
	return ::UpdateWindow(m_hWnd);
}

//MiniApp class

class MiniApp
{
public:
	MiniApp();
	bool InitInstance();
	bool Run();
	MiniWnd* m_pMainWnd;
};

bool MiniApp::InitInstance()
{
	// TODO: Add your implementation code here.
	m_pMainWnd = new MiniWnd;
	bool b = m_pMainWnd->Create();
	m_pMainWnd->ShowWindow();
	m_pMainWnd->UpdateWindow();

	return b;
}


bool MiniApp::Run()
{
	// TODO: Add your implementation code here.
		//5.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

MiniApp::MiniApp()
{
	InitInstance();
	Run();
}