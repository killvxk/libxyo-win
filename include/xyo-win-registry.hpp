//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_REGISTRY_H
#define XYO_WIN_REGISTRY_H

#ifndef XYO_WIN_HPP
#include "xyo-win.hpp"
#endif


namespace XYO {
	namespace Win {

		class Registry {
			public:

				XYO_WIN_EXPORT static BOOL createKey(HKEY, char *);
				XYO_WIN_EXPORT static BOOL createKeyVolatile(HKEY, char *);
				XYO_WIN_EXPORT static BOOL writeString(HKEY, char *, char *, char *);
				XYO_WIN_EXPORT static BOOL writeDWord(HKEY, char *, char *, unsigned long int);
				XYO_WIN_EXPORT static BOOL readString(HKEY, char *, char *, char *, unsigned long int, char *);
				XYO_WIN_EXPORT static BOOL readDWord(HKEY, char *, char *, unsigned long int *, unsigned long int);
				XYO_WIN_EXPORT static BOOL deleteKey(HKEY, char *, char *, BOOL);
				XYO_WIN_EXPORT static BOOL getStringLength(HKEY masterkey, char *key, char *reg, LPDWORD out);

				XYO_WIN_EXPORT static BOOL createKeyW(HKEY, wchar_t *);
				XYO_WIN_EXPORT static BOOL createKeyVolatileW(HKEY, wchar_t *);
				XYO_WIN_EXPORT static BOOL writeStringW(HKEY, wchar_t *, wchar_t *, wchar_t *);
				XYO_WIN_EXPORT static BOOL writeDWordW(HKEY, wchar_t *, wchar_t *, unsigned long int);
				XYO_WIN_EXPORT static BOOL readStringW(HKEY, wchar_t *, wchar_t *, wchar_t *, unsigned long int, wchar_t *);
				XYO_WIN_EXPORT static BOOL readDWordW(HKEY, wchar_t *, wchar_t *, unsigned long int *, unsigned long int);
				XYO_WIN_EXPORT static BOOL deleteKeyW(HKEY, wchar_t *, wchar_t *, BOOL);
				XYO_WIN_EXPORT static BOOL getStringLengthW(HKEY masterkey, wchar_t *key, wchar_t *reg, LPDWORD out);

		};

	};
};

#endif


