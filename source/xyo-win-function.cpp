//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include <windows.h>
#include <string.h>
#include <ole2.h>
#include <shlobj.h>
#include <docobj.h>
#include <mshtml.h>
#include <exdisp.h>
#include <exdispid.h>
#include <stdio.h>

#include "xyo-win-function.hpp"

namespace XYO {
	namespace Win {

		Function::Function() {
			functionName_ = NULL;
			dispIdMember_ = 0;
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			VariantInit(&varResult_);
			refObject_ = NULL;
		};

		Function::~Function() {
			if (functionName_ != NULL) {
				SysFreeString(functionName_);
			}
			VariantClear(&varResult_);
			releaseObject();
		};

		void Function::setObject(IDispatch *x) {
			if (x != NULL) {
				x->AddRef();
			};
			if (refObject_ != NULL) {
				refObject_->Release();
			};
			refObject_ = x;
		};

		void Function::releaseObject() {
			if (refObject_ != NULL) {
				refObject_->Release();
			};
			refObject_ = NULL;
		};

		void Function::functionName(BSTR Name) {
			if (functionName_ != NULL) {
				SysFreeString(functionName_);
			}
			functionName_ = SysAllocString(Name);
			dispIdMember_ = 0;
		};

		HRESULT Function::invoke() {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 0;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 1;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v1, Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 2;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[1], v1.value());
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v2, Variant v1, Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 3;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[2], v2.value());
			VariantCopy(&pDispParams.rgvarg[1], v1.value());
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v3, Variant v2, Variant v1, Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 4;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[3], v3.value());
			VariantCopy(&pDispParams.rgvarg[2], v2.value());
			VariantCopy(&pDispParams.rgvarg[1], v1.value());
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v4, Variant v3, Variant v2, Variant v1, Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 5;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[4], v4.value());
			VariantCopy(&pDispParams.rgvarg[3], v3.value());
			VariantCopy(&pDispParams.rgvarg[2], v2.value());
			VariantCopy(&pDispParams.rgvarg[1], v1.value());
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v5, Variant v4, Variant v3, Variant v2, Variant v1, Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 6;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[5], v5.value());
			VariantCopy(&pDispParams.rgvarg[4], v4.value());
			VariantCopy(&pDispParams.rgvarg[3], v3.value());
			VariantCopy(&pDispParams.rgvarg[2], v2.value());
			VariantCopy(&pDispParams.rgvarg[1], v1.value());
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v6, Variant v5, Variant v4, Variant v3, Variant v2, Variant v1, Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 7;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[6], v6.value());
			VariantCopy(&pDispParams.rgvarg[5], v5.value());
			VariantCopy(&pDispParams.rgvarg[4], v4.value());
			VariantCopy(&pDispParams.rgvarg[3], v3.value());
			VariantCopy(&pDispParams.rgvarg[2], v2.value());
			VariantCopy(&pDispParams.rgvarg[1], v1.value());
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

		HRESULT Function::invoke(Variant v7, Variant v6, Variant v5, Variant v4, Variant v3, Variant v2, Variant v1, Variant v0) {
			HRESULT retVal;
			DISPPARAMS pDispParams;
			UINT k;
			if (refObject_ == NULL) {
				return E_INVALIDARG;
			}
			if (dispIdMember_ == 0) {
				retVal = getDispatchId();
				if (retVal != S_OK) {
					return retVal;
				}
			};
			memset(&exceptInfo_, 0, sizeof (exceptInfo_));
			nArgErr_ = (UINT) - 1;
			memset(&pDispParams, 0, sizeof (pDispParams));
			pDispParams.cArgs = 8;
			pDispParams.rgvarg = new VARIANTARG[pDispParams.cArgs];
			pDispParams.cNamedArgs = 0;
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantInit(&pDispParams.rgvarg[k]);
			}
			VariantCopy(&pDispParams.rgvarg[7], v7.value());
			VariantCopy(&pDispParams.rgvarg[6], v6.value());
			VariantCopy(&pDispParams.rgvarg[5], v5.value());
			VariantCopy(&pDispParams.rgvarg[4], v4.value());
			VariantCopy(&pDispParams.rgvarg[3], v3.value());
			VariantCopy(&pDispParams.rgvarg[2], v2.value());
			VariantCopy(&pDispParams.rgvarg[1], v1.value());
			VariantCopy(&pDispParams.rgvarg[0], v0.value());
			VariantClear(&varResult_);
			VariantInit(&varResult_);
			retVal = refObject_->Invoke(dispIdMember_, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &pDispParams, &varResult_, &exceptInfo_, &nArgErr_);
			for (k = 0; k < pDispParams.cArgs; k++) {
				VariantClear(&pDispParams.rgvarg[k]);
			}
			delete[] pDispParams.rgvarg;
			return retVal;
		};

	};
};

