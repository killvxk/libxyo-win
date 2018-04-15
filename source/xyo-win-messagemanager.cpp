//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include <windows.h>
#include <stdio.h>

#include "xyo-win-messagemanager.hpp"
#include "xyo-win-tnotify.hpp"

namespace XYO {
	namespace Win {

		using namespace XYO;
		using namespace XYO::Core;

		MessageManager::MessageManager() {
			InitializeCriticalSection(&cs_);
		};

		MessageManager::~MessageManager() {
			WindowList::Node *x;
			for (x = windowList_.head; x!=NULL; x=x->next) {
				x->value->setNotifyOnDestroy(NULL);
			};
			windowList_.empty();
			DeleteCriticalSection(&cs_);
		};

		typedef void (MessageManager::*eventDestroy_)(MessageManager::WindowList::Node *);

		MessageManager::WindowList::Node *MessageManager::add(Window *p) {
			WindowList::Node *retV;
			TPointer<TNotify<MessageManager, eventDestroy_,WindowList::Node *> > n;

			EnterCriticalSection(&cs_);
			retV = windowList_.pushToTailX(p);
			LeaveCriticalSection(&cs_);

			n.newMemory();
			n->set(this, &MessageManager::eventOnDestroy_, retV);
			p->setNotifyOnDestroy(n.value());
			return retV;
		};

		void MessageManager::remove(WindowList::Node *window) {
			EnterCriticalSection(&cs_);
			windowList_.extractNode(window);
			LeaveCriticalSection(&cs_);
			window->value.deleteMemory();
			windowList_.deleteNode(window);
		};

		int MessageManager::processAllMessages() {
			MSG msg;
			WindowList::Node *scan;
			msg.wParam = 0;
			while (!windowList_.isEmpty()) {
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
					if (msg.message == WM_QUIT) {
						break;
					};
					for (scan = windowList_.head; scan!=NULL; scan=scan->next) {
						if ((scan->value.value())->translateAccelerator(msg)) {
							break;
						};
					};
					if (scan!=nullptr) {
						continue;
					};
					if (IsWindow(msg.hwnd)) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					};
				} else {
					WaitForSingleObject(GetCurrentThread(), 1);
				};
			};
			while (!windowList_.isEmpty()) {
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
					if (IsWindow(msg.hwnd)) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					};
				} else {
					WaitForSingleObject(GetCurrentThread(), 1);
					if (!windowList_.isEmpty()) {
						DestroyWindow(*((windowList_.head)->value.value()));
					};
				};
			};
			return (int)msg.wParam;
		};

		void MessageManager::eventOnDestroy_(WindowList::Node *window) {
			window->value->setNotifyOnDestroy(nullptr);
			remove(window);
		};

		void MessageManager::postMessageToAll(UINT m) {
			WindowList::Node *x;
			for (x = windowList_.head; x!=NULL; x=x->next) {
				PostMessage(*(x->value.value()), m, 0, 0);
			};
		};

		void MessageManager::sendMessageToAll(UINT m) {
			WindowList::Node *x;
			for (x = windowList_.head; x!=NULL; x=x->next) {
				SendMessage(*(x->value.value()), m, 0, 0);
			};
		};

		void MessageManager::initMemory() {
			WindowList::initMemory();
		};

	};
};

