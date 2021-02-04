#include "cServer.h"
#include <sstream>

cServer::cServer(void)
{
	Connections = NULL;
	Delay = 100;
	Connections = (SOCKET*)calloc(64,sizeof(SOCKET));
	Client_Count = 0;
}


void cServer::Init(int port ,HWND &wnd)
{
	WORD ver = MAKEWORD(2,2);

	if(WSAStartup(ver,&data) != 0)
		MessageBox(NULL,"Call to WSAStartup failed!","ERROR",MB_OK | MB_ICONERROR);
	
	

	
	


	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	

	
	
	Listen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	if(bind(Listen,(sockaddr*)&addr,sizeof(addr)))
		MessageBox(NULL,"Call to bind failed!","ERROR",MB_OK | MB_ICONERROR);
	
	listen(Listen,SOMAXCONN);



	
	char * buf = new char[512];
	

	gethostname(buf,512);
	
	struct hostent *host = gethostbyname(buf);
	
	if(host)
	{
		
		sprintf(this->ip, "%d.%d.%d.%d",
			(unsigned char)host->h_addr_list[0][0],
			(unsigned char)host->h_addr_list[0][1],
			(unsigned char)host->h_addr_list[0][2],
			(unsigned char)host->h_addr_list[0][3]);
		
	}
	
	InvalidateRect(wnd,NULL,TRUE);


	
	delete [] buf;

	

}

void cServer::ServerLoop()
{
	
	struct sockaddr_in client_in;
	int client_size_addr = sizeof(client_in);

	HANDLE hThreads[64];


	for(;;Sleep(75))
	{
		if(Client_Count >=  64) //64 - Connections length;
		{
			for(int i = 0; i < 64; i++)
			{
				TerminateThread(hThreads[i], 0);
				closesocket(Connections[i]);
			}
			Client_Count = 0;

			
		}
			
			
		if(Connections[Client_Count] = accept(Listen,(sockaddr*)&client_in,&client_size_addr))
		{
		
			Client_Count++;
			hThreads[Client_Count - 1] =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ThreadReceive,(LPVOID)this,NULL,NULL);
		}

	
	}

	for(int i = 0; i < this->Client_Count;i++)
	{
		closesocket(Connections[i]);
	}
	free(Connections);

	closesocket(this->Client);
	closesocket(this->Listen);
	WSACleanup();
}


void cServer::Receive(int ID) 
{
	char buffer[1024] = "";
	
	for(;;Sleep(75))
	{
		ZeroMemory(buffer,1024);
		if(recv(Connections[ID],buffer,1024,0))
		{
			if(strcmp(buffer,"") != -1 && strlen(buffer) > 1)
			{
				if(strchr(buffer, '`') != NULL)
					Processing(buffer);
				else
					Processing(buffer);
			}
				
		}
		
	}
}

void cServer::Processing(char buffer[]) 
{
	if(!PrintMessage(buffer, '<', CharPos::BEGIN_STRING, true))
		if(!PrintMessage(buffer, '#', CharPos::BEGIN_STRING, false))
			PrintMessage(buffer, NULL, CharPos::ALL_STRING, false);

}

void cServer::ProcessingBuffer(char buffer, bool withPause) const
{

			switch(buffer)
			{
			//COMMON_CHARS
			case '&':
				Emulate(VK_RETURN,false, withPause);
				break;
			case ',':
				Emulate(VK_OEM_COMMA,false, withPause);
				break;
			case '.':
				Emulate(VK_OEM_PERIOD,false, withPause);
				break;
			case ' ':
				Emulate(VK_SPACE,false, withPause);
				break;
			case '`':
				
				Emulate(VK_OEM_3,false, withPause);
				break;
			case '!':
				Emulate((DWORD)Chars::num1,true,withPause);
				break;
			case '?':
				Emulate(VK_OEM_2,true, withPause);
				break;
			case '+':
				Emulate(VK_OEM_PLUS,false, withPause);
				break;
			case '-':
				Emulate(VK_OEM_MINUS,false, withPause);
				break;
			case '_':
				Emulate(VK_OEM_MINUS,false, withPause);
				break;

			//LOVERCASE
			case 'q':
				Emulate((DWORD)Chars::q,false, withPause);
				break;
			case 'w':
				Emulate((DWORD)Chars::w,false, withPause);
				break;
			case 'e':
				Emulate((DWORD)Chars::e,false, withPause);
				break;
			case 'r':
				Emulate((DWORD)Chars::r,false, withPause);
				break;
			case 't':
				Emulate((DWORD)Chars::t,false, withPause);
				break;
			case 'y':
				Emulate((DWORD)Chars::y,false, withPause);
				break;
			case 'u':
				Emulate((DWORD)Chars::u,false, withPause);
				break;
			case 'i':
				Emulate((DWORD)Chars::i,false, withPause);
				break;
			case 'o':
				Emulate((DWORD)Chars::o,false, withPause);
				break;
			case 'p':
				Emulate((DWORD)Chars::p,false, withPause);
				break;
			case 'a':
				Emulate((DWORD)Chars::a,false, withPause);
				break;
			case 's':
				Emulate((DWORD)Chars::s,false, withPause);
				break;
			case 'd':
				Emulate((DWORD)Chars::d,false, withPause);
				break;
			case 'f':
				Emulate((DWORD)Chars::f,false, withPause);
				break;
			case 'g':
				Emulate((DWORD)Chars::g,false, withPause);
				break;
			case 'h':
				Emulate((DWORD)Chars::h,false, withPause);
				break;
			case 'j':
				Emulate((DWORD)Chars::j,false, withPause);
				break;
			case 'k':
				Emulate((DWORD)Chars::k,false, withPause);
				break;
			case 'l':
				Emulate((DWORD)Chars::l,false, withPause);
				break;
			case 'z':
				Emulate((DWORD)Chars::z,false, withPause);
				break;
			case 'x':
				Emulate((DWORD)Chars::x,false, withPause);
				break;
			case 'c':
				Emulate((DWORD)Chars::c,false, withPause);
				break;
			case 'v':
				Emulate((DWORD)Chars::v,false, withPause);
				break;
			case 'b':
				Emulate((DWORD)Chars::b,false, withPause);
				break;
			case 'n':
				Emulate((DWORD)Chars::n,false, withPause);
				break;
			case 'm':
				Emulate((DWORD)Chars::m,false, withPause);
				break;
				//UPPERCASE
			case 'Q':
				Emulate((DWORD)Chars::q,true,withPause);
				break;
			case 'W':
				Emulate((DWORD)Chars::w,true,withPause);
				break;
			case 'E':
				Emulate((DWORD)Chars::e,true,withPause);
				break;
			case 'R':
				Emulate((DWORD)Chars::r,true,withPause);
				break;
			case 'T':
				Emulate((DWORD)Chars::t,true,withPause);
				break;
			case 'Y':
				Emulate((DWORD)Chars::y,true,withPause);
				break;
			case 'U':
				Emulate((DWORD)Chars::u,true,withPause);
				break;
			case 'I':
				Emulate((DWORD)Chars::i,true,withPause);
				break;
			case 'O':
				Emulate((DWORD)Chars::o,true,withPause);
				break;
			case 'P':
				Emulate((DWORD)Chars::p,true,withPause);
				break;
			case 'A':
				Emulate((DWORD)Chars::a,true,withPause);
				break;
			case 'S':
				Emulate((DWORD)Chars::s,true,withPause);
				break;
			case 'D':
				Emulate((DWORD)Chars::d,true,withPause);
				break;
			case 'F':
				Emulate((DWORD)Chars::f,true,withPause);
				break;
			case 'G':
				Emulate((DWORD)Chars::g,true,withPause);
				break;
			case 'H':
				Emulate((DWORD)Chars::h,true,withPause);
				break;
				//Numbers (0-9)
			case '0':
				Emulate((DWORD)Chars::num0, false, withPause);
				break;
			case '1':
				Emulate((DWORD)Chars::num1, false, withPause);
				break;
			case '2':
				Emulate((DWORD)Chars::num2, false, withPause);
				break;
			case '3':
				Emulate((DWORD)Chars::num3, false, withPause);
				break;
			case '4':
				Emulate((DWORD)Chars::num4, false, withPause);
				break;
			case '5':
				Emulate((DWORD)Chars::num5, false, withPause);
				break;
			case '6':
				Emulate((DWORD)Chars::num6, false, withPause);
				break;
			case '7':
				Emulate((DWORD)Chars::num7, false, withPause);
				break;
			case '8':
				Emulate((DWORD)Chars::num8, false, withPause);
				break;
			case '9':
				Emulate((DWORD)Chars::num9, false, withPause);
				break;
			}
}

bool cServer::PrintMessage(char buffer[] ,char Char, CharPos pos, bool withPause)
{
	std::string temp(buffer);

		if(pos == CharPos::ALL_STRING)
		for(int i = 0; i < strlen(buffer); i++)
		{
			ProcessingBuffer(buffer[i], false);
		}


	if(pos == CharPos::BEGIN_STRING)
	if(buffer[0] == Char && strlen(buffer) > 1)
	{
		
		if(Char == '#')
		{
			keybd_event(VK_LCONTROL, 0, 0, 0);
			keybd_event(VK_MENU, 0, 0, 0);
			Emulate(VK_OEM_3, true);
			keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
		}
		if(Char == '<'  && strchr(buffer, '>') != NULL)
		{
			char* str = strtok(buffer,"<");
			str = strtok(buffer, ">");

			for(int o = 0; o < strlen(str); o++)
				str[o] = str[o+1];

			this->Delay = atoi(str);
			
			
			

				

			for(int i = strlen(str) + 1; i < temp.length(); i++)
			{
				ProcessingBuffer(temp[i], true);
			}


		}
			return true;
	}
	return false;
}

void cServer::Emulate(DWORD BtnID,bool isUppercase, bool withPause) const
{
	if(isUppercase)
	{
		keybd_event(VK_LSHIFT, MapVirtualKey(VK_LSHIFT, 0), KEYEVENTF_EXTENDEDKEY | 0, 0);

		keybd_event(BtnID,  MapVirtualKey(BtnID,0), KEYEVENTF_EXTENDEDKEY | 0, 0);
		if(withPause)
		Sleep(Delay);
		keybd_event(BtnID, MapVirtualKey(BtnID,0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

		keybd_event(VK_LSHIFT,MapVirtualKey(VK_LSHIFT, 0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
	}
	else
	{


		

		keybd_event(BtnID,MapVirtualKey(BtnID,0), KEYEVENTF_EXTENDEDKEY | 0, 0);
		if(withPause)
		Sleep(Delay);
		keybd_event(BtnID,MapVirtualKey(BtnID,0), KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
	}

}

char* cServer::GetIp()
{
	if(this->ip != "NULL")
		return ip;
	return "NULL";

}

cServer::~cServer(void)
{	

	
}
