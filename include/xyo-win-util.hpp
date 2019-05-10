//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_UTIL_HPP
#define XYO_WIN_UTIL_HPP

#ifndef XYO_WIN_HPP
#include "xyo-win.hpp"
#endif

namespace XYO
{
	namespace Win
	{
		namespace Util
		{

			XYO_WIN_EXPORT void sendMessageToAllChildWindowsIE(HWND hParendWnd, UINT MessageId, WPARAM wParam, LPARAM lParam);
			XYO_WIN_EXPORT void postMessageToProcessWindows(UINT MessageId, WPARAM wParam, LPARAM lParam);

		};
	};
};

#endif

