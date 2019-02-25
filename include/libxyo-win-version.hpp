//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef LIBXYO_WIN_VERSION_HPP
#define LIBXYO_WIN_VERSION_HPP

#define LIBXYO_WIN_VERSION_ABCD                 2,0,0,41
#define LIBXYO_WIN_VERSION_STR                 "2.0.0"
#define LIBXYO_WIN_VERSION_STR_BUILD           "41"
#define LIBXYO_WIN_VERSION_STR_DATETIME        "2019-02-25 11:50:54"

#ifndef XYO_RC

#ifndef XYO_WIN__EXPORT_HPP
#include "xyo-win--export.hpp"
#endif

namespace Lib {
	namespace XYO {
		namespace Win {
			namespace Version {
				XYO_WIN_EXPORT const char *version();
				XYO_WIN_EXPORT const char *build();
				XYO_WIN_EXPORT const char *versionWithBuild();
				XYO_WIN_EXPORT const char *datetime();
			};
		};
	};
};

#endif
#endif

