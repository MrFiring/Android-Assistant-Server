#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

enum CharPos
{
	BEGIN_STRING,
	ALL_STRING,
};


enum Chars
{
	q = 0x51,
	w = 0x57,
	e = 0x45,
	r = 0x52,
	t = 0x54,
	y = 0x59,
	u = 0x55,
	i = 0x49,
	o = 0x4F,
	p = 0x50,
	a = 0x41,
	s = 0x53,
	d = 0x44,
	f = 0x46,
	g = 0x47,
	h = 0x48,
	j = 0x4A,
	k = 0x4B,
	l = 0x4C,
	z = 0x5A,
	x = 0x58,
	c = 0x43,
	v = 0x56,
	b = 0x42,
	n = 0x4E,
	m = 0x4D,
	num0 = 0x30,
	num1 = 0x31,
	num2 = 0x32,
	num3 = 0x33,
	num4 = 0x34,
	num5 = 0x35,
	num6 = 0x36,
	num7 = 0x37,
	num8 = 0x38,
	num9 = 0x39,
};


class cServer
{
private:
	WSAData data;


	SOCKET *Connections;
	SOCKET Client;
	SOCKET Listen;

	int Client_Count;
	char ip[15];
	int Delay;///100


public:
	cServer(void);
	void Init(int port ,HWND &wnd);
	void ServerLoop();

	void Receive(int ID) ; //Receive messages from client.
	void Processing(char buffer[]); //Processing received messages and emulate input.
	void ProcessingBuffer(char buffer, bool withPause) const; 
	bool PrintMessage(char buffer[] ,char Char, CharPos pos, bool withPause) ;

	char* GetIp();
	int GetClientsCount() const { return this->Client_Count;}

	void Emulate(DWORD BtnID,bool isUppercase = false, bool withPause = false) const;

	static void ThreadReceive(cServer &server)
	{
	server.Receive(server.GetClientsCount() - 1);
	}

	~cServer(void);
};




