//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include <windows.h>
#include <string.h>
#include <stdio.h>

#include "xyo-win-application.hpp"

namespace XYO {
	namespace Win {

		int Application::main(int cmdN, char *cmdS[]) {
			int retV;

			messageManager_.newMemory();

			retV = parseCommandLine(cmdN,cmdS);
			if (retV != 0) {
				return retV;
			}

			if(!newWindow(SW_SHOWDEFAULT,true)) {
				return -1;
			};

			return messageManager_->processAllMessages();
		};

		void Application::setWndclassEx(WNDCLASSEX &) {
		};

		void Application::setCreateStruct(CREATESTRUCT &) {
		};

		int Application::setShowCmd(int x) {
			return x;
		};

		int Application::parseCommandLine(int cmdN, char *cmdS[]) {
			return 0;
		};

		void Application::initWndclassEx(WNDCLASSEX &wndclassEx) {
			memset(&wndclassEx, 0, sizeof (wndclassEx));

			wndclassEx.cbSize = sizeof (wndclassEx);
			wndclassEx.style = CS_BYTEALIGNCLIENT | CS_CLASSDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
			wndclassEx.cbClsExtra = 0;
			wndclassEx.cbWndExtra = 0;
			wndclassEx.hInstance = GetModuleHandle(NULL);
			wndclassEx.hIcon = LoadIcon(wndclassEx.hInstance, IDI_APPLICATION);
			wndclassEx.hCursor = LoadCursor(wndclassEx.hInstance, IDC_ARROW);
			wndclassEx.hbrBackground = (HBRUSH) (COLOR_APPWORKSPACE + 1);
			wndclassEx.lpszMenuName = NULL;
			wndclassEx.lpszClassName = "Class.Unknown";
			wndclassEx.hIconSm = NULL;
		};

		void Application::initCreateStruct(CREATESTRUCT &createStruct,WNDCLASSEX &wndclassEx) {
			memset(&createStruct, 0, sizeof (createStruct));
			createStruct.lpCreateParams = NULL;
			createStruct.hInstance = GetModuleHandle(NULL);
			createStruct.hMenu = NULL;
			createStruct.hwndParent = NULL;
			createStruct.cy = CW_USEDEFAULT;
			createStruct.cx = CW_USEDEFAULT;
			createStruct.y = CW_USEDEFAULT;
			createStruct.x = CW_USEDEFAULT;
			createStruct.style = WS_OVERLAPPED | WS_BORDER | WS_CLIPCHILDREN | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME;
			createStruct.lpszName = "Unknown";
			createStruct.lpszClass = wndclassEx.lpszClassName;
			createStruct.dwExStyle = WS_EX_APPWINDOW | WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE;
		};

		bool Application::newWindow(int cmdShow,bool regWndClass) {
			WNDCLASSEX wndclassEx;
			CREATESTRUCT createStruct;

			initWndclassEx(wndclassEx);
			setWndclassEx(wndclassEx);

			if(regWndClass) {
				if (!registerClass(wndclassEx)) {
					return false;
				};
			};

			initCreateStruct(createStruct,wndclassEx);
			setCreateStruct(createStruct);

			if (!create(createStruct.dwExStyle,
				    createStruct.lpszClass,
				    createStruct.lpszName,
				    createStruct.style,
				    createStruct.x, createStruct.y, createStruct.cx, createStruct.cy,
				    createStruct.hwndParent,
				    createStruct.hMenu,
				    createStruct.hInstance)) {
				return false;
			};

			ShowWindow(*this, setShowCmd(cmdShow));
			messageManager_->add(this);
			return true;
		};

		void Application::initMemory() {
			TPointer<MessageManager>::initMemory();
		};

	};
};

