//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_WINDOW_HPP
#define XYO_WIN_WINDOW_HPP

#ifndef XYO_WIN_HPP
#include "xyo-win.hpp"
#endif

#ifndef XYO_WIN_INOTIFY_HPP
#include "xyo-win-inotify.hpp"
#endif

namespace XYO {
	namespace Win {

		class Window :
			public virtual Core::Object {
			private:
				HWND hWnd_;
				XYO_WIN_EXPORT static LRESULT CALLBACK windowProcedure_(HWND hWnd,
						UINT uMsg,
						WPARAM wParam,
						LPARAM lParam);
				XYO_WIN_EXPORT bool destroyAndWait_();

				Core::TPointer<INotify> notifyOnCreate_;
				Core::TPointer<INotify> notifyOnDestroy_;

				XYO_CORE_DISALLOW_COPY_ASSIGN_MOVE(Window);
			public:

				XYO_WIN_EXPORT Window();
				XYO_WIN_EXPORT ~Window();

				inline operator HWND() {
					return hWnd_;
				};

				XYO_WIN_EXPORT operator HINSTANCE();

				XYO_WIN_EXPORT virtual LRESULT windowProcedure(UINT uMsg, WPARAM wParam, LPARAM lParam);
				XYO_WIN_EXPORT virtual bool translateAccelerator(MSG &msg);

				XYO_WIN_EXPORT bool create(DWORD dwExStyle,
							   LPCTSTR lpClassName,
							   LPCTSTR lpWindowName,
							   DWORD dwStyle,
							   int x, int y,
							   int nWidth, int nHeight,
							   HWND hWndParent,
							   HMENU hMenu,
							   HINSTANCE hInstance);

				XYO_WIN_EXPORT bool create(LPCTSTR lpClassName,
							   LPCTSTR lpWindowName,
							   DWORD dwStyle,
							   int x, int y,
							   int nWidth, int nHeight,
							   HWND hWndParent,
							   HMENU hMenu,
							   HINSTANCE hInstance);

				XYO_WIN_EXPORT void setNotifyOnCreate(INotify *);
				XYO_WIN_EXPORT void setNotifyOnDestroy(INotify *);

				XYO_WIN_EXPORT static bool registerClass(WNDCLASS &);
				XYO_WIN_EXPORT static bool registerClass(WNDCLASSEX &);

				XYO_WIN_EXPORT static void initMemory();
		};

	};
};

#endif

