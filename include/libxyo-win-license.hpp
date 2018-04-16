//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef LIBXYO_WIN_LICENSE_HPP
#define LIBXYO_WIN_LICENSE_HPP

#ifndef XYO_WIN__EXPORT_HPP
#include "xyo-win--export.hpp"
#endif

namespace Lib {
	namespace XYO {
		namespace Win {

			class License {
				public:
					XYO_WIN_EXPORT static const char *content();
					XYO_WIN_EXPORT static const char *shortContent();
			};

		};
	};
};

#endif
