//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_FUNCTION_HPP
#define XYO_WIN_FUNCTION_HPP

#ifndef XYO_WIN_VARIANT_HPP
#include "xyo-win-variant.hpp"
#endif

namespace XYO {
	namespace Win {

		class Function :
			public virtual Core::Object {
			protected:
				BSTR functionName_;
				DISPID dispIdMember_;
				EXCEPINFO exceptInfo_;
				VARIANTARG varResult_;
				IDispatch *refObject_;
				UINT nArgErr_;

				XYO_CORE_DISALLOW_COPY_ASSIGN_MOVE(Function);
			public:
				XYO_WIN_EXPORT Function();
				XYO_WIN_EXPORT ~Function();

				XYO_WIN_EXPORT void setObject(IDispatch *);
				XYO_WIN_EXPORT void releaseObject();

				inline IDispatch *getObject() {
					return refObject_;
				};

				XYO_WIN_EXPORT void functionName(BSTR Name);

				inline BSTR functionName() {
					return functionName_;
				};

				inline VARIANTARG *result() {
					return &varResult_;
				};

				inline EXCEPINFO *exceptInfo() {
					return &exceptInfo_;
				};

				inline DISPID dispatchId() {
					return dispIdMember_;
				};

				inline UINT argErr() {
					return nArgErr_;
				};

				inline HRESULT getDispatchId() {
					return refObject_->GetIDsOfNames(IID_NULL, &functionName_, 1, LOCALE_SYSTEM_DEFAULT, &dispIdMember_);
				};

				XYO_WIN_EXPORT HRESULT invoke();
				XYO_WIN_EXPORT HRESULT invoke(Variant);
				XYO_WIN_EXPORT HRESULT invoke(Variant, Variant);
				XYO_WIN_EXPORT HRESULT invoke(Variant, Variant, Variant);
				XYO_WIN_EXPORT HRESULT invoke(Variant, Variant, Variant, Variant);
				XYO_WIN_EXPORT HRESULT invoke(Variant, Variant, Variant, Variant, Variant);
				XYO_WIN_EXPORT HRESULT invoke(Variant, Variant, Variant, Variant, Variant, Variant);
				XYO_WIN_EXPORT HRESULT invoke(Variant, Variant, Variant, Variant, Variant, Variant, Variant);
				XYO_WIN_EXPORT HRESULT invoke(Variant, Variant, Variant, Variant, Variant, Variant, Variant, Variant);
		};

	};
};

#endif

