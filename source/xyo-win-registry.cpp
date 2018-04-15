//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include <stdio.h>
#include <windows.h>

#include "xyo-win-registry.hpp"

namespace XYO {
	namespace Win {

		BOOL Registry::createKey(HKEY masterkey, char *key) {
			HKEY mykey;
			if (RegCreateKeyExA(masterkey, key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &mykey, NULL) != ERROR_SUCCESS) {
				return FALSE;
			}
			RegCloseKey(mykey);
			return TRUE;
		};

		BOOL Registry::createKeyVolatile(HKEY masterkey, char *key) {
			HKEY mykey;
			if (RegCreateKeyExA(masterkey, key, 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &mykey, NULL) != ERROR_SUCCESS) {
				return FALSE;
			}
			RegCloseKey(mykey);
			return TRUE;
		};

		BOOL Registry::writeString(HKEY masterkey, char *key, char *reg, char *_str) {
			HKEY mykey;
			BOOL retval;
			if (RegOpenKeyExA(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				return FALSE;
			}
			if (RegSetValueExA(mykey, reg, 0, REG_SZ, (BYTE *) _str, (DWORD)strlen(_str) + 1) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
			}
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::writeDWord(HKEY masterkey, char *key, char *reg, unsigned long int val) {
			HKEY mykey;
			BOOL retval;
			if (RegOpenKeyExA(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				return FALSE;
			}
			if (RegSetValueExA(mykey, reg, 0, REG_DWORD, (BYTE *) & val, sizeof (unsigned long int)) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
			}
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::readString(HKEY masterkey, char *key, char *reg, char *_str, unsigned long int sz, char *def) {
			HKEY mykey;
			BOOL retval;
			unsigned long int type = REG_SZ;
			if (RegOpenKeyExA(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				strcpy(_str, def);
				return FALSE;
			};
			if (RegQueryValueExA(mykey, reg, NULL, &type, (BYTE *) _str, &sz) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
				strcpy(_str, def);
			};
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::readDWord(HKEY masterkey, char *key, char *reg, unsigned long int *_str, unsigned long int def) {
			HKEY mykey;
			BOOL retval;
			unsigned long int type = REG_DWORD;
			unsigned long int sz = sizeof (unsigned long int);
			if (RegOpenKeyExA(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				*_str = def;
				return FALSE;
			};
			if (RegQueryValueExA(mykey, reg, NULL, &type, (BYTE *) _str, &sz) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
				*_str = def;
			};
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::deleteKey(HKEY masterkey, char *key, char *reg, BOOL value) {
			HKEY mykey;
			BOOL retval;
			if (RegOpenKeyExA(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				return FALSE;
			}
			if (value) {
				if (RegDeleteValueA(mykey, reg) == ERROR_SUCCESS) {
					retval = TRUE;
				} else {
					retval = FALSE;
				}
			} else {
				if (RegDeleteKeyA(mykey, reg) == ERROR_SUCCESS) {
					retval = TRUE;
				} else {
					retval = FALSE;
				}
			};
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::getStringLength(HKEY masterkey, char *key, char *reg, LPDWORD out) {
			HKEY mykey;
			BOOL retval;
			unsigned long int type = REG_SZ;
			if (out == NULL) {
				return FALSE;
			}

			if (RegOpenKeyEx(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				*out = 0;
				return FALSE;
			};
			if (RegQueryValueEx(mykey, reg, NULL, &type, NULL, out) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
				*out = 0;
			};
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::createKeyW(HKEY masterkey, wchar_t *key) {
			HKEY mykey;
			if (RegCreateKeyExW(masterkey, key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &mykey, NULL) != ERROR_SUCCESS) {
				return FALSE;
			}
			RegCloseKey(mykey);
			return TRUE;
		};

		BOOL Registry::createKeyVolatileW(HKEY masterkey, wchar_t *key) {
			HKEY mykey;
			if (RegCreateKeyExW(masterkey, key, 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &mykey, NULL) != ERROR_SUCCESS) {
				return FALSE;
			}
			RegCloseKey(mykey);
			return TRUE;
		};

		BOOL Registry::writeStringW(HKEY masterkey, wchar_t *key, wchar_t *reg, wchar_t *_str) {
			HKEY mykey;
			BOOL retval;
			if (RegOpenKeyExW(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				return FALSE;
			}
			if (RegSetValueExW(mykey, reg, 0, REG_SZ, (BYTE *) _str, (DWORD)wcslen(_str) + 1) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
			}
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::writeDWordW(HKEY masterkey, wchar_t *key, wchar_t *reg, unsigned long int val) {
			HKEY mykey;
			BOOL retval;
			if (RegOpenKeyExW(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				return FALSE;
			}
			if (RegSetValueExW(mykey, reg, 0, REG_DWORD, (BYTE *) & val, sizeof (unsigned long int)) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
			}
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::readStringW(HKEY masterkey, wchar_t *key, wchar_t *reg, wchar_t *_str, unsigned long int sz, wchar_t *def) {
			HKEY mykey;
			BOOL retval;
			unsigned long int type = REG_SZ;
			if (RegOpenKeyExW(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				wcscpy(_str, def);
				return FALSE;
			};
			if (RegQueryValueExW(mykey, reg, NULL, &type, (BYTE *) _str, &sz) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
				wcscpy(_str, def);
			};
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::readDWordW(HKEY masterkey, wchar_t *key, wchar_t *reg, unsigned long int *_str, unsigned long int def) {
			HKEY mykey;
			BOOL retval;
			unsigned long int type = REG_DWORD;
			unsigned long int sz = sizeof (unsigned long int);
			if (RegOpenKeyExW(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				*_str = def;
				return FALSE;
			};
			if (RegQueryValueExW(mykey, reg, NULL, &type, (BYTE *) _str, &sz) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
				*_str = def;
			};
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::deleteKeyW(HKEY masterkey, wchar_t *key, wchar_t *reg, BOOL value) {
			HKEY mykey;
			BOOL retval;
			if (RegOpenKeyExW(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				return FALSE;
			}
			if (value) {
				if (RegDeleteValueW(mykey, reg) == ERROR_SUCCESS) {
					retval = TRUE;
				} else {
					retval = FALSE;
				}
			} else {
				if (RegDeleteKeyW(mykey, reg) == ERROR_SUCCESS) {
					retval = TRUE;
				} else {
					retval = FALSE;
				}
			};
			RegCloseKey(mykey);
			return retval;
		};

		BOOL Registry::getStringLengthW(HKEY masterkey, wchar_t *key, wchar_t *reg, LPDWORD out) {
			HKEY mykey;
			BOOL retval;
			unsigned long int type = REG_SZ;
			if (out == NULL) {
				return FALSE;
			}

			if (RegOpenKeyExW(masterkey, key, 0, KEY_ALL_ACCESS, &mykey) != ERROR_SUCCESS) {
				*out = 0;
				return FALSE;
			};
			if (RegQueryValueExW(mykey, reg, NULL, &type, NULL, out) == ERROR_SUCCESS) {
				retval = TRUE;
			} else {
				retval = FALSE;
				*out = 0;
			};
			RegCloseKey(mykey);
			return retval;
		};

	};
};

