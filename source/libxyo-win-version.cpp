//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "libxyo-win-version.hpp"

namespace Lib {
	namespace XYO {
		namespace Win {
			namespace Version {

				static const char *version_="2.0.0";
				static const char *build_="41";
				static const char *versionWithBuild_="2.0.0.41";
				static const char *datetime_="2019-02-25 11:50:54";

				const char *version() {
					return version_;
				};
				const char *build() {
					return build_;
				};
				const char *versionWithBuild() {
					return versionWithBuild_;
				};
				const char *datetime() {
					return datetime_;
				};

			};
		};
	};
};



