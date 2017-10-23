// WSAEventSelect.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

SOCKET		g_ClientSock;
bool		g_bShutdown;
WSAEVENT	g_hClientEvent;

bool InitNetwork()
{
	int retval;

	//-----------------------------------------------------------------------------------
	// Winsock 초기화
	//-----------------------------------------------------------------------------------
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;


	//-----------------------------------------------------------------------------------
	// socket()
	//-----------------------------------------------------------------------------------
	g_ClientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (g_ClientSock == INVALID_SOCKET)
		return false;

	//-----------------------------------------------------------------------------------
	// WSAEvent 생성
	//-----------------------------------------------------------------------------------
	g_hClientEvent = WSACreateEvent();
	if (g_hClientEvent == WSA_INVALID_EVENT)
		return false;

	//-----------------------------------------------------------------------------------
	// SOCKET과 EVENT 짝짓기
	//-----------------------------------------------------------------------------------
	retval = WSAEventSelect(g_ClientSock, g_hClientEvent, FD_CONNECT | FD_CLOSE | FD_READ | FD_WRITE);

	//-----------------------------------------------------------------------------------	
	// SOCKADDR 생성
	//-----------------------------------------------------------------------------------
	SOCKADDR_IN sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(dfNETWORK_PORT);
	InetPton(AF_INET, dfNETWORK_IP, &sockaddr.sin_addr.s_addr);

	//-----------------------------------------------------------------------------------
	// Connect
	//-----------------------------------------------------------------------------------
	retval = connect(g_ClientSock, (SOCKADDR *)&sockaddr, sizeof(sockaddr));
	if (retval == SOCKET_ERROR)
	{
		retval = WSAGetLastError();
		if (retval != WSAEWOULDBLOCK)
			return FALSE;
	}

	return TRUE;
}

void netIOProcess()
{
	int retval;

	SOCKET Socket;
	WSAEVENT hEvent;
	WSANETWORKEVENTS NetworkEvents;

	retval = WSAWaitForMultipleEvents(1, &g_hClientEvent, FALSE, WSA_INFINITE, FALSE);
	if (retval == WSA_WAIT_FAILED)
	{
		//error
	}

	retval = 

}

void update()
{

}

void monitor()

{

}

int _tmain(int argc, _TCHAR* argv[])
{
	g_bShutdown = false;
	InitNetwork();

	while (!g_bShutdown)
	{
		netIOProcess();
		update();

		monitor();
	}

	return 0;
}