//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_USER_HPP
#define XYO_WIN_USER_HPP

#ifndef XYO_WIN_HPP
#include "xyo-win.hpp"
#endif

namespace XYO {
	namespace Win {

		class User {
			public:

				XYO_WIN_EXPORT static HRESULT addToUserGroupsUser(IADsUser *pUser,BSTR UserName);
				XYO_WIN_EXPORT static HRESULT createUserAccountOnAD(wchar_t *UserName,wchar_t *FullName,wchar_t *Description,wchar_t *Password,wchar_t *ComputerName,wchar_t *ComputerNameAndUser,wchar_t *ThisComputerNameAndUser);
				XYO_WIN_EXPORT static HRESULT removeUserAccountOnAD(wchar_t *ComputerNameAndUser);
				XYO_WIN_EXPORT static HRESULT removeUserFromItsGroups(IADsUser *pUser,BSTR UserName);
				XYO_WIN_EXPORT static bool hideUserFromWelcomeScreen(wchar_t *_user_name);
				XYO_WIN_EXPORT static bool showUserInWelcomeScreen(wchar_t *_user_name);
				XYO_WIN_EXPORT static bool createUserAccountAsCurrentUserPrivilegeOnLocalComputer(wchar_t *_user_name,wchar_t *_password,wchar_t *_full_name,wchar_t *_description);
				XYO_WIN_EXPORT static bool deleteUserAccountOnLocalComputer(wchar_t *_user_name);
				XYO_WIN_EXPORT static bool createHiddenUserAccountAsCurrentUserPrivilegeOnLocalComputer(wchar_t *_user_name,wchar_t *_password,wchar_t *_full_name,wchar_t *_description);
		};


	};
};

#endif

