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


namespace XYO
{
	namespace Win
	{
		namespace Registry
		{

			XYO_WIN_EXPORT BOOL createKey(HKEY, char *);
			XYO_WIN_EXPORT BOOL createKeyVolatile(HKEY, char *);
			XYO_WIN_EXPORT BOOL writeString(HKEY, char *, char *, char *);
			XYO_WIN_EXPORT BOOL writeDWord(HKEY, char *, char *, unsigned long int);
			XYO_WIN_EXPORT BOOL readString(HKEY, char *, char *, char *, unsigned long int, char *);
			XYO_WIN_EXPORT BOOL readDWord(HKEY, char *, char *, unsigned long int *, unsigned long int);
			XYO_WIN_EXPORT BOOL deleteKey(HKEY, char *, char *, BOOL);
			XYO_WIN_EXPORT BOOL getStringLength(HKEY masterkey, char *key, char *reg, LPDWORD out);

			XYO_WIN_EXPORT BOOL createKeyW(HKEY, wchar_t *);
			XYO_WIN_EXPORT BOOL createKeyVolatileW(HKEY, wchar_t *);
			XYO_WIN_EXPORT BOOL writeStringW(HKEY, wchar_t *, wchar_t *, wchar_t *);
			XYO_WIN_EXPORT BOOL writeDWordW(HKEY, wchar_t *, wchar_t *, unsigned long int);
			XYO_WIN_EXPORT BOOL readStringW(HKEY, wchar_t *, wchar_t *, wchar_t *, unsigned long int, wchar_t *);
			XYO_WIN_EXPORT BOOL readDWordW(HKEY, wchar_t *, wchar_t *, unsigned long int *, unsigned long int);
			XYO_WIN_EXPORT BOOL deleteKeyW(HKEY, wchar_t *, wchar_t *, BOOL);
			XYO_WIN_EXPORT BOOL getStringLengthW(HKEY masterkey, wchar_t *key, wchar_t *reg, LPDWORD out);



		};
	};
};

#endif


