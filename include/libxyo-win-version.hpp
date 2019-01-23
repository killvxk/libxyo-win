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

#define LIBXYO_WIN_VERSION_ABCD                 1,0,0,40
#define LIBXYO_WIN_VERSION_STR                 "1.0.0"
#define LIBXYO_WIN_VERSION_STR_BUILD           "40"
#define LIBXYO_WIN_VERSION_STR_DATETIME        "2018-05-07 02:08:10"

#ifndef XYO_RC

#ifndef XYO_WIN__EXPORT_HPP
#include "xyo-win--export.hpp"
#endif

namespace Lib {
	namespace XYO {
		namespace Win {

			class Version {
				public:
					XYO_WIN_EXPORT static const char *getVersion();
					XYO_WIN_EXPORT static const char *getBuild();
					XYO_WIN_EXPORT static const char *getVersionWithBuild();
					XYO_WIN_EXPORT static const char *getDatetime();
			};

		};
	};
};

#endif
#endif

