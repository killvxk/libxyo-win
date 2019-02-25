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

				static const char *version_="%VERSION_VERSION%";
				static const char *build_="%VERSION_BUILD%";
				static const char *versionWithBuild_="%VERSION_VERSION%.%VERSION_BUILD%";
				static const char *datetime_="%VERSION_DATETIME%";

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



