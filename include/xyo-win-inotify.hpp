//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_INOTIFY_HPP
#define XYO_WIN_INOTIFY_HPP

#ifndef XYO_WIN_HPP
#include "xyo-win.hpp"
#endif

namespace XYO
{
	namespace Win
	{

		class INotify :
			public virtual Core::Object
		{
				XYO_CORE_INTERFACE(INotify);

			public:
				virtual void notify() = 0;
		};

	};
};

#endif
