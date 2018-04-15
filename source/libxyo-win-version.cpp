//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "libxyo-win-version.hpp"

namespace Lib {
	namespace XYO {
		namespace Win {

			static const char *versionVersion="1.0.0";
			static const char *versionBuild="39";
			static const char *versionVersionWithBuild="1.0.0.39";
			static const char *versionDatetime="2018-04-16 02:06:16";

			const char *Version::getVersion() {
				return versionVersion;
			};
			const char *Version::getBuild() {
				return versionBuild;
			};
			const char *Version::getVersionWithBuild() {
				return versionVersionWithBuild;
			};
			const char *Version::getDatetime() {
				return versionDatetime;
			};

		};
	};
};



