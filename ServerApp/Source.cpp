#include <io.h>
#include <stdio.h>
#include <sstream>
#include "cServer.h"
#include <Windows.h>
#include <CommCtrl.h>
#include "resource.h"


#define DEFAULT_DELAY 50

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK dlgSettingsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Server();//Init and Start server loop.
void Receive(int ID); //Receive messages from client.
void Processing(char buffer[]); //Processing received messages and emulate input.
void Emulate(DWORD BtnID,bool isUppercase);
void ProcessingBuffer(char buffer); 
bool PrintMessage(char buffer[] ,char Char, CharPos pos, bool withPause);

static void ThreadLoop();

HWND Window; //Window descriptor
HINSTANCE hInst; // Cur hInstance


cServer server;





int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCommandLine, int nCmdShow)
{

	
	WNDCLASSEX cl;
	
	cl.cbSize = sizeof(WNDCLASSEX);
	cl.hInstance = hInstance;
	cl.lpfnWndProc = WndProc;
	cl.cbClsExtra = 0;
	cl.cbWndExtra = 0;
	cl.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	cl.hCursor = LoadCursor(hInstance,IDC_ARROW);
	cl.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	cl.hIconSm = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	cl.lpszMenuName = NULL; 
	cl.style = CS_HREDRAW | CS_VREDRAW;
	cl.lpszClassName = "GeneralClass";
	
	hInst = hInstance;

	if(!RegisterClassEx(&cl))
	{
		MessageBox(NULL, "Call to RegisterClassEx(cl) failed!","ERROR", MB_ICONERROR | MB_OK);
		return -1;
	}
	
	InitCommonControls();


	//Create Server thread
	

	server.Init(45879, Window);
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ThreadLoop,(LPVOID)&server,NULL,NULL);

	//347.150
	Window = CreateWindowEx(0,"GeneralClass","Assistant",WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,205,107,NULL,NULL,hInstance,NULL);
	if(!Window)
		MessageBox(NULL, "Call to CreateWindow failed!","ERROR", MB_ICONERROR | MB_OK);
	
	

	ShowWindow(Window,nCmdShow);
	UpdateWindow(Window);
	




	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	
	return 0;
}

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	
	switch(msg)
	{
		case WM_PAINT:
			{
			hdc = BeginPaint(hwnd,&ps);
	
			std::stringstream str;
			str << "Your IP: " << server.GetIp();
			SetBkMode(hdc,TRANSPARENT);

			
			
			TextOut(hdc,25,35,str.str().c_str(), strlen(str.str().c_str()));
			
			EndPaint(hwnd, &ps);
			break;
			}
		
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
			break;
	}
	return 0;
}

static void ThreadLoop()
{
	server.ServerLoop();
}


