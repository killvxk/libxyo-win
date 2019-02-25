//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef LIBXYO_WIN_COPYRIGHT_HPP
#define LIBXYO_WIN_COPYRIGHT_HPP

#define LIBXYO_WIN_COPYRIGHT            "Copyright (c) Grigore Stefan"
#define LIBXYO_WIN_PUBLISHER            "Grigore Stefan"
#define LIBXYO_WIN_COMPANY              LIBXYO_WIN_PUBLISHER
#define LIBXYO_WIN_CONTACT              "g_stefan@yahoo.com"
#define LIBXYO_WIN_FULL_COPYRIGHT       LIBXYO_WIN_COPYRIGHT " <" LIBXYO_WIN_CONTACT ">"

#ifndef XYO_RC

#ifndef XYO_WIN__EXPORT_HPP
#include "xyo-win--export.hpp"
#endif

namespace Lib {
	namespace XYO {
		namespace Win {
			namespace Copyright {
				XYO_WIN_EXPORT const char *copyright();
				XYO_WIN_EXPORT const char *publisher();
				XYO_WIN_EXPORT const char *company();
				XYO_WIN_EXPORT const char *contact();
				XYO_WIN_EXPORT const char *fullCopyright();
			};
		};
	};
};

#endif
#endif
