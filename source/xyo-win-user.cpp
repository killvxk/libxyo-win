//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef SECURITY_WIN32
#define SECURITY_WIN32
#endif

#include <windows.h>
#include <objbase.h>
#include <iads.h>
#include <adshlp.h>
#include <wininet.h>
#include <Iptypes.h>
#include <Iphlpapi.h>
#include <Security.h>
#include <stdio.h>

#include "xyo-win-user.hpp"
#include "xyo-win-registry.hpp"

namespace XYO {
	namespace Win {


		using namespace XYO::Core;

		HRESULT User::addToUserGroupsUser(IADsUser *pUser,BSTR UserName) {

			VARIANT var;
			IADsGroup *pADs;
			ULONG lFetch;
			IDispatch *pDisp;
			IUnknown *pUnk;
			IEnumVARIANT *pEnum;


			IADsMembers *pGroups;
			HRESULT hr = S_OK;
			hr = pUser->Groups(&pGroups);


			if (FAILED(hr)) {
				return hr;
			};

			hr = pGroups->get__NewEnum(&pUnk);
			pGroups->Release();

			if (FAILED(hr)) {
				return hr;
			};


			hr = pUnk->QueryInterface(IID_IEnumVARIANT,(void **)&pEnum);
			pUnk->Release();

			if (FAILED(hr)) {
				return hr;
			};

			VariantInit(&var);
			hr = pEnum->Next(1, &var, &lFetch);
			while(hr == S_OK) {
				if (lFetch == 1) {
					pDisp = V_DISPATCH(&var);
					pDisp->QueryInterface(IID_IADsGroup, (void **)&pADs);

					pADs->Add(UserName);

					pADs->Release();
				};
				VariantClear(&var);
				pDisp=NULL;
				hr = pEnum->Next(1, &var, &lFetch);
			};

			hr = pEnum->Release();
			return S_OK;

		};

		HRESULT User::createUserAccountOnAD(wchar_t *UserName,wchar_t *FullName,wchar_t *Description,wchar_t *Password,wchar_t *ComputerName,wchar_t *ComputerNameAndUser,wchar_t *ThisComputerNameAndUser) {

			HRESULT hr;
			BSTR  _ComputerName;
			BSTR  _User;
			BSTR  _UserName;
			BSTR  _Password;
			BSTR  _FullName;
			BSTR  _Description;
			BSTR  _userAccountControl;
			BSTR  _sAMAccountName;
			BSTR  _userFlags;
			BSTR  _ComputerNameAndUser;
			IADsContainer *pUsers=NULL;
			IDispatch *pDisp=NULL;
			IADsUser *padsUser=NULL;

			if((ComputerName==NULL)||
			   (UserName==NULL)||
			   (Password==NULL)||
			   (FullName==NULL)||
			   (Description==NULL)) {
				return E_INVALIDARG;
			};

			_ComputerName=SysAllocString(ComputerName);
			_User=SysAllocString(L"user");
			_UserName=SysAllocString(UserName);
			_Password=SysAllocString(Password);
			_FullName=SysAllocString(FullName);
			_Description=SysAllocString(Description);
			_userAccountControl=SysAllocString(L"UserAccountControl");
			_sAMAccountName=SysAllocString(L"SAMAccountName");
			_userFlags=SysAllocString(L"UserFlags");
			_ComputerNameAndUser=SysAllocString(ComputerNameAndUser);

			if((_ComputerName==NULL)||
			   (_User==NULL)||
			   (_UserName==NULL)||
			   (_Password==NULL)||
			   (_FullName==NULL)||
			   (_userAccountControl==NULL)||
			   (_sAMAccountName==NULL)||
			   (_userFlags==NULL)||
			   (_ComputerNameAndUser==NULL)||
			   (_Description==NULL)) {
				if(_ComputerName!=NULL) {
					SysFreeString(_ComputerName);
				}
				if(_User!=NULL) {
					SysFreeString(_User);
				}
				if(_UserName!=NULL) {
					SysFreeString(_UserName);
				}
				if(_Password!=NULL) {
					SysFreeString(_Password);
				}
				if(_FullName!=NULL) {
					SysFreeString(_FullName);
				}
				if(_Description!=NULL) {
					SysFreeString(_Description);
				}
				if(_userAccountControl!=NULL) {
					SysFreeString(_userAccountControl);
				}
				if(_userFlags!=NULL) {
					SysFreeString(_userFlags);
				}
				if(_sAMAccountName!=NULL) {
					SysFreeString(_sAMAccountName);
				}
				if(_ComputerNameAndUser!=NULL) {
					SysFreeString(_ComputerNameAndUser);
				}
				return E_OUTOFMEMORY;
			};

			hr=ADsGetObject(_ComputerName, IID_IADsContainer, (LPVOID *)&pUsers);
			if(SUCCEEDED(hr)) {
				hr=pUsers->Create(_User,_UserName, &pDisp);
				if(SUCCEEDED(hr)) {
					hr=pDisp->QueryInterface(IID_IADsUser,(void **)&padsUser);
					if(SUCCEEDED(hr)) {
						VARIANT value;
						VariantInit(&value);
						value.vt=VT_BSTR;
						value.bstrVal=SysAllocString(_FullName);
						hr=padsUser->Put(_sAMAccountName,value);
						VariantClear(&value);
						hr=padsUser->put_FullName(_FullName);
						hr=padsUser->put_Description(_Description);
						hr=padsUser->SetInfo();
						hr=padsUser->SetPassword(_Password);
						hr=padsUser->put_AccountDisabled(FALSE);
						hr=padsUser->put_PasswordRequired(TRUE);
						VariantInit(&value);
						hr=padsUser->Get(_userAccountControl,&value);
						if(SUCCEEDED(hr)) {
							value.lVal|=ADS_UF_DONT_EXPIRE_PASSWD;
							hr=padsUser->Put(_userAccountControl,value);
						};
						VariantClear(&value);
						VariantInit(&value);
						hr=padsUser->Get(_userFlags,&value);
						if(SUCCEEDED(hr)) {
							value.lVal|=ADS_UF_DONT_EXPIRE_PASSWD;
							hr=padsUser->Put(_userFlags,value);
						};
						VariantClear(&value);
						hr=padsUser->SetInfo();
						padsUser->Release();


						hr=ADsGetObject(ThisComputerNameAndUser, IID_IADsUser, (LPVOID *)&padsUser);
						if(SUCCEEDED(hr)) {
							hr=addToUserGroupsUser(padsUser,_ComputerNameAndUser);
							padsUser->Release();
						};
					};
					pDisp->Release();
				};
				pUsers->Release();
			};
			SysFreeString(_ComputerName);
			SysFreeString(_User);
			SysFreeString(_UserName);
			SysFreeString(_Password);
			SysFreeString(_FullName);
			SysFreeString(_Description);
			SysFreeString(_userAccountControl);
			SysFreeString(_sAMAccountName);
			SysFreeString(_userFlags);
			SysFreeString(_ComputerNameAndUser);
			return hr;

		};

		HRESULT User::removeUserAccountOnAD(wchar_t *ComputerNameAndUser) {

			HRESULT hr = S_OK;
			IADsUser *padsUser=NULL;
			IADsContainer *padsContainer=NULL;
			BSTR ADsClass;
			hr=ADsGetObject(ComputerNameAndUser, IID_IADsUser, (LPVOID *)&padsUser);
			if(SUCCEEDED(hr)) {
				hr=padsUser->get_Class(&ADsClass);
				if(SUCCEEDED(hr)) {
					if(lstrcmpiW(ADsClass,L"user")==0) {
						SysFreeString(ADsClass);
						hr=padsUser->get_Parent(&ADsClass);
						if(SUCCEEDED(hr)) {
							hr=ADsGetObject(ADsClass,IID_IADsContainer,(LPVOID *)&padsContainer);
							SysFreeString(ADsClass);
							if(SUCCEEDED(hr)) {
								hr=padsUser->get_Name(&ADsClass);
								if(SUCCEEDED(hr)) {
									removeUserFromItsGroups(padsUser,ADsClass);
									padsUser->Release();
									padsContainer->Delete(L"user",ADsClass);
									SysFreeString(ADsClass);
									padsContainer->Release();
									return hr;
								};
								padsContainer->Release();
							} else {
								padsUser->Release();
							};
							return hr;
						};
					} else {
						SysFreeString(ADsClass);
					};
				};
				padsUser->Release();
			};
			return hr;

		};

		HRESULT User::removeUserFromItsGroups(IADsUser *pUser,BSTR UserName) {

			VARIANT var;
			IADsGroup *pADs;
			ULONG lFetch;
			IDispatch *pDisp;
			IUnknown *pUnk;
			IEnumVARIANT *pEnum;


			IADsMembers *pGroups;
			HRESULT hr = S_OK;
			hr = pUser->Groups(&pGroups);

			if (FAILED(hr)) {
				return hr;
			}

			hr = pGroups->get__NewEnum(&pUnk);
			pGroups->Release();

			if (FAILED(hr)) {
				return hr;
			}


			hr = pUnk->QueryInterface(IID_IEnumVARIANT,(void **)&pEnum);
			pUnk->Release();
			if (FAILED(hr)) {
				return hr;
			}

			VariantInit(&var);
			hr = pEnum->Next(1, &var, &lFetch);
			while(hr == S_OK) {
				if (lFetch == 1) {
					pDisp = V_DISPATCH(&var);
					pDisp->QueryInterface(IID_IADsGroup, (void **)&pADs);
					if(pADs) {
						pADs->Remove(UserName);
						pADs->Release();
					};
				}
				VariantClear(&var);
				pDisp=NULL;
				hr = pEnum->Next(1, &var, &lFetch);
			};
			hr = pEnum->Release();
			return S_OK;

		};

		bool User::hideUserFromWelcomeScreen(wchar_t *_user_name) {

			if(Registry::createKeyW(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\SpecialAccounts")) {
				if(Registry::createKeyW(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\SpecialAccounts\\UserList")) {
					if(Registry::writeDWordW(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\SpecialAccounts\\UserList",_user_name,0x00010000)) {
						return false;
					};
				};
			};
			return false;

		};

		bool User::showUserInWelcomeScreen(wchar_t *_user_name) {

			if(Registry::deleteKeyW(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\\SpecialAccounts\\UserList",_user_name,TRUE)) {
				return true;
			};
			return false;

		};

		bool User::createUserAccountAsCurrentUserPrivilegeOnLocalComputer(wchar_t *_user_name,wchar_t *_password,wchar_t *_full_name,wchar_t *_description) {

			wchar_t buffer[2048];
			DWORD bufferSize;

			wchar_t computerName[256];
			wchar_t computerNameAndUser[512];
			wchar_t thisNameAndUser[1024];
			int k;

			bufferSize=(DWORD)2048;
			if(GetComputerNameExW(ComputerNameDnsFullyQualified,(LPWSTR)buffer,&bufferSize)) {
				wcscpy(computerName,L"WinNT://");
				wcscpy(computerNameAndUser,computerName);
				wcscpy(thisNameAndUser,computerName);

				wcscat(computerName,buffer);
				wcscat(computerName,L",Computer");
				wcscat(computerNameAndUser,buffer);
				wcscat(computerNameAndUser,L"/");
				wcscat(computerNameAndUser,_user_name);
				wcscat(computerNameAndUser,L",User");

				bufferSize=(DWORD)2048;
				if(GetUserNameExW(NameSamCompatible,(LPWSTR)buffer,&bufferSize)) {

					wcscat(thisNameAndUser,buffer);
					wcscat(thisNameAndUser,L",User");
					for(k=0; thisNameAndUser[k]!=0; ++k) {
						if(thisNameAndUser[k]==L'\\') {
							thisNameAndUser[k]=L'/';
						};
					};
					if(FAILED(createUserAccountOnAD(_user_name,_full_name,_description,_password,computerName,computerNameAndUser,thisNameAndUser))) {
					} else {
						return true;
					};

				};
			};
			return false;

		};

		bool User::deleteUserAccountOnLocalComputer(wchar_t *_user_name) {

			wchar_t buffer[2048];
			DWORD bufferSize;
			wchar_t computerNameAndUser[1024];

			bufferSize=(DWORD)2048;
			if(GetComputerNameExW(ComputerNameDnsFullyQualified,(LPWSTR)buffer,&bufferSize)) {

				wcscpy(computerNameAndUser,L"WinNT://");
				wcscat(computerNameAndUser,buffer);
				wcscat(computerNameAndUser,L"/");
				wcscat(computerNameAndUser,_user_name);
				wcscat(computerNameAndUser,L",User");
				showUserInWelcomeScreen(_user_name);

				if(FAILED(removeUserAccountOnAD(computerNameAndUser))) {
				} else {
					return true;
				};

			};
			return false;

		};

		bool User::createHiddenUserAccountAsCurrentUserPrivilegeOnLocalComputer(wchar_t *_user_name,wchar_t *_password,wchar_t *_full_name,wchar_t *_description) {
			if(createUserAccountAsCurrentUserPrivilegeOnLocalComputer(_user_name,_full_name,_password,_description)) {
				hideUserFromWelcomeScreen(_user_name);
				return true;
			};
			return false;

		};

	};
};

