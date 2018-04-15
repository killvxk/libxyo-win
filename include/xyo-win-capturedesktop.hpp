//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_CAPTUREDESKTOP_HPP
#define XYO_WIN_CAPTUREDESKTOP_HPP

#ifndef XYO_WIN_HPP
#include "xyo-win.hpp"
#endif

namespace XYO {
	namespace Win {

		class CaptureDesktop {
			public:

				XYO_WIN_EXPORT static bool captureDesktopToPNGFile(char *fileName);

		};

	};
};

#endif

