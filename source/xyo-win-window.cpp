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

#include "xyo-win-window.hpp"

namespace XYO {
	namespace Win {

		Window::Window() {
			hWnd_ = NULL;
		};

		Window::~Window() {
			destroyAndWait_();
		};

		Window::operator HINSTANCE() {
#ifdef XYO_APPLICATION_32BIT
			return (HINSTANCE) GetWindowLong(hWnd_, GWL_HINSTANCE);
#endif
#ifdef XYO_APPLICATION_64BIT
			return (HINSTANCE) GetWindowLongPtr(hWnd_, GWLP_HINSTANCE);
#endif
		};

		bool Window::destroyAndWait_() {
			if (hWnd_ == NULL) {
				return false;
			}
			if (hWnd_ != NULL) {
				DestroyWindow(hWnd_);
			};
			while (hWnd_ != NULL) {
				WaitForSingleObject(GetCurrentThread(), 1);
			};
			return true;
		};

		LRESULT Window::windowProcedure(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			return DefWindowProc(hWnd_, uMsg, wParam, lParam);
		};

		LRESULT CALLBACK Window::windowProcedure_(HWND hWnd,
				UINT uMsg,
				WPARAM wParam,
				LPARAM lParam) {
			Window *vWindow;
			if (uMsg == WM_NCCREATE) {
				vWindow = (Window *) (((LPCREATESTRUCT) lParam)->lpCreateParams);
				vWindow->incReferenceCount();
				vWindow->hWnd_ = hWnd;

#ifdef XYO_APPLICATION_32BIT
				SetWindowLong(hWnd, 0, (DWORD) vWindow);
#endif
#ifdef XYO_APPLICATION_64BIT
				SetWindowLongPtr(hWnd, 0, (LONG_PTR) vWindow);
#endif

				if (vWindow->notifyOnCreate_.isValid()) {
					vWindow->notifyOnCreate_->notify();
				};
			};

#ifdef XYO_APPLICATION_32BIT
			vWindow = (Window *) GetWindowLong(hWnd, 0);
#endif
#ifdef XYO_APPLICATION_64BIT
			vWindow = (Window *) GetWindowLongPtr(hWnd, 0);
#endif
			if (vWindow != NULL) {
				if (uMsg == WM_NCDESTROY) {

#ifdef XYO_APPLICATION_32BIT
					SetWindowLong(hWnd, 0, 0);
#endif
#ifdef XYO_APPLICATION_64BIT
					SetWindowLongPtr(hWnd, 0, NULL);
#endif

					LRESULT retVal = vWindow->windowProcedure(uMsg, wParam, lParam);
					if (vWindow->notifyOnDestroy_.isValid()) {
						vWindow->notifyOnDestroy_->notify();
					};
					vWindow->hWnd_ = NULL;
					vWindow->decReferenceCount();
					return retVal;
				} else {
					return vWindow->windowProcedure(uMsg, wParam, lParam);
				};
			};
			return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		};

		bool Window::create(DWORD dwExStyle,
				    LPCTSTR lpClassName,
				    LPCTSTR lpWindowName,
				    DWORD dwStyle,
				    int x, int y,
				    int nWidth, int nHeight,
				    HWND hWndParent,
				    HMENU hMenu,
				    HINSTANCE hInstance) {
			return (::CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, this) != NULL);
		};

		bool Window::create(LPCTSTR lpClassName,
				    LPCTSTR lpWindowName,
				    DWORD dwStyle,
				    int x, int y,
				    int nWidth, int nHeight,
				    HWND hWndParent,
				    HMENU hMenu,
				    HINSTANCE hInstance) {
			return (::CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, this) != NULL);
		};

		bool Window::registerClass(WNDCLASS &wc) {
			wc.lpfnWndProc = Window::windowProcedure_;
			wc.cbWndExtra = sizeof (void *);
			return ::RegisterClass(&wc) != 0;
		};

		bool Window::registerClass(WNDCLASSEX &wc) {
			wc.cbSize = sizeof (WNDCLASSEX);
			wc.lpfnWndProc = Window::windowProcedure_;
			wc.cbWndExtra = sizeof (void *);
			return ::RegisterClassEx(&wc) != 0;
		};

		void Window::setNotifyOnCreate(INotify *value) {
			notifyOnCreate_ = value;
		};

		void Window::setNotifyOnDestroy(INotify *value) {
			notifyOnDestroy_ = value;
		};

		bool Window::translateAccelerator(MSG &msg) {
			msg;
			return false;
		};

		void Window::initMemory() {
			Core::TPointer<INotify>::initMemory();
		};

	};
};

