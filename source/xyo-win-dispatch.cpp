//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include <windows.h>
#include <string.h>
#include <oleauto.h>
#include <stdio.h>

#pragma warning(disable:4100)

#include "xyo-win-dispatch.hpp"

namespace XYO {
	namespace Win {

		void Dispatch::setDispatchFunctionsIdAndNames() {
		};

		//IUnknown

		HRESULT STDMETHODCALLTYPE Dispatch::QueryInterface(REFIID riid, LPVOID *ppvObj) {
			if (memcmp(&riid, &IID_IUnknown, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IUnknown *> (this);
			} else if (memcmp(&riid, &IID_IDispatch, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IDispatch *> (this);
			} else {
				*ppvObj = NULL;
				return (E_NOINTERFACE);
			};
			return (S_OK);
		};

		ULONG STDMETHODCALLTYPE Dispatch::AddRef() {
			return (ULONG)1;
		};

		ULONG STDMETHODCALLTYPE Dispatch::Release() {
			return (ULONG)1;
		};

		//IDispatch

		HRESULT STDMETHODCALLTYPE Dispatch::GetTypeInfoCount(UINT *) {
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE Dispatch::GetTypeInfo(UINT, LCID, LPTYPEINFO *) {
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE Dispatch::GetIDsOfNames(REFIID, LPOLESTR *names, UINT count, LCID, DISPID *outID) {
			UINT k;
			for (k = 0; k < count; ++k) {
				outID[k] = 0;
			};
			return invokeAndId(0, 0, NULL, NULL, names, count, outID);
		};

		HRESULT STDMETHODCALLTYPE Dispatch::Invoke(DISPID dispIdMember, REFIID, LCID, WORD, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *, UINT *) {
			return invokeAndId(1, dispIdMember, pDispParams, pVarResult, NULL, 0, NULL);
		};

		::IDispatch *Dispatch::getIDispatchValue() {
			return static_cast<::IDispatch *> (this);
		};

		HRESULT Dispatch::invokeAndId(UINT mode, DISPID dispIdMember, DISPPARAMS *pDispParams, VARIANT *pVarResult, LPOLESTR *names, UINT count, DISPID *outID) {
			if (mode == 0) {
				return (S_FALSE);
			};
			if (mode == 1) {
				return (DISP_E_MEMBERNOTFOUND);
			};
			return (S_FALSE);
		};

	};
};


