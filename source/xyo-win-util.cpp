//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef SECURITY_WIN32
#define SECURITY_WIN32
#endif

#include <windows.h>
#include <objbase.h>
#include <iads.h>
#include <adshlp.h>
#include <wininet.h>
#include <Iptypes.h>
#include <Iphlpapi.h>
#include <Security.h>
#include <stdio.h>

#include "xyo-win-util.hpp"

namespace XYO
{
	namespace Win
	{
		namespace Util
		{

			using namespace XYO::Core;

			typedef struct
			{
				UINT MessageId;
				WPARAM wParam;
				LPARAM lParam;
			} SMessage, * PSMessage;


			static BOOL CALLBACK EnumChildProcIE_(HWND hwnd, LPARAM lParam)
			{
				PSMessage psMessage = (PSMessage)lParam;
				char buf[1024];
				buf[0] = 0;
				GetClassName(hwnd, buf, 1024);
				if(strcmp(buf, "Internet Explorer_Server") == 0)
				{
					SendMessage(hwnd, psMessage->MessageId, psMessage->wParam, psMessage->lParam);
				};
				return TRUE;
			};

			void sendMessageToAllChildWindowsIE(HWND hParendWnd, UINT MessageId, WPARAM wParam, LPARAM lParam)
			{
				SMessage sMessage;
				sMessage.MessageId = MessageId;
				sMessage.wParam = wParam;
				sMessage.lParam = lParam;

				EnumChildWindows(hParendWnd, EnumChildProcIE_, (LPARAM)&sMessage);
			};

			static BOOL CALLBACK EnumProcessWindowsProc_(HWND hwnd, LPARAM lParam)
			{
				PSMessage psMessage = (PSMessage)lParam;
				DWORD processId;

				GetWindowThreadProcessId(hwnd, &processId);
				if(processId == GetCurrentProcessId())
				{
					PostMessage(hwnd, psMessage->MessageId, psMessage->wParam, psMessage->lParam);
				};
				return TRUE;
			};

			void postMessageToProcessWindows(UINT MessageId, WPARAM wParam, LPARAM lParam)
			{
				SMessage sMessage;
				sMessage.MessageId = MessageId;
				sMessage.wParam = wParam;
				sMessage.lParam = lParam;

				EnumWindows(EnumProcessWindowsProc_, (LPARAM)&sMessage);
			};

		};
	};
};

