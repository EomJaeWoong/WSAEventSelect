// WSAEventSelect.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

SOCKET		g_ClientSock;
bool		g_bShutdown;
WSAEVENT	g_hClientEvent;

bool InitNetwork()
{
	int retval;

	//-----------------------------------------------------------------------------------
	// Winsock �ʱ�ȭ
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
	// WSAEvent ����
	//-----------------------------------------------------------------------------------
	g_hClientEvent = WSACreateEvent();
	if (g_hClientEvent == WSA_INVALID_EVENT)
		return false;

	//-----------------------------------------------------------------------------------
	// SOCKET�� EVENT ¦����
	//-----------------------------------------------------------------------------------
	retval = WSAEventSelect(g_ClientSock, g_hClientEvent, FD_CONNECT | FD_CLOSE | FD_READ | FD_WRITE);

	//-----------------------------------------------------------------------------------	
	// SOCKADDR ����
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