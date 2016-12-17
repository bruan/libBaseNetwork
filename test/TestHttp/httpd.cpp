#include "network.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <signal.h>
#endif

#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <map>
#include "http_server.h"
#include "http_response.h"
#include "http_request.h"

using namespace std;

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4996)
#endif

#define ISspace(x) isspace((int)(x))
#ifndef _countof
#define _countof(elem) sizeof(elem)/sizeof(elem[0])
#endif


int main()
{
#ifndef _WIN32
	// ��������һ���Ѿ��رյ�socketд���ݵ��½�����ֹ
	struct sigaction sig_action;
	memset(&sig_action, 0, sizeof(sig_action));
	sig_action.sa_handler = SIG_IGN;
	sig_action.sa_flags = 0;
	sigaction(SIGPIPE, &sig_action, 0);

	// �����ն˶Ͽ�����SIGHUP�źŵ��½�����ֹ
	memset(&sig_action, 0, sizeof(sig_action));
	sig_action.sa_handler = SIG_IGN;
	sig_action.sa_flags = 0;
	sigaction(SIGHUP, &sig_action, 0);
#endif

	net::startupNetwork(nullptr);

	http::CHttpServer* pHttpServer = new http::CHttpServer();
	SNetAddr netAddr;
	netAddr.nPort = 8000;
	strncpy(netAddr.szHost, "0.0.0.0", sizeof(netAddr.szHost));

	pHttpServer->registerCallback("/aaa", [](const http::CHttpRequest& sRequest, http::CHttpResponse& sResponse)->void
	{
		sResponse.write("Hello");
		sResponse.write("World");
	});

	pHttpServer->registerDir("/bbb", "bbb");
	pHttpServer->start(netAddr, 10000);

	return 0;
}

#ifdef _WIN32
#pragma warning(pop)
#endif