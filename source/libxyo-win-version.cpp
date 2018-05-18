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
			static const char *versionBuild="40";
			static const char *versionVersionWithBuild="1.0.0.40";
			static const char *versionDatetime="2018-05-07 02:08:10";

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



