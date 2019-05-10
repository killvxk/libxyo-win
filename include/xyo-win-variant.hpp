//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_VARIANT_HPP
#define XYO_WIN_VARIANT_HPP

#ifndef XYO_WIN_HPP
#include "xyo-win.hpp"
#endif

namespace XYO
{
	namespace Win
	{

		class Variant:
			public virtual Core::Object
		{
			protected:
				VARIANTARG var_;
			public:

				inline Variant::Variant()
				{
					VariantInit(&var_);
				};

				inline Variant::~Variant()
				{
					VariantClear(&var_);
				};

				inline Variant::Variant(const Variant &x)
				{
					VariantInit(&var_);
					VariantCopy(&var_, &x.var_);
				};

				inline Variant::Variant(const VARIANTARG &x)
				{
					VariantInit(&var_);
					VariantCopy(&var_, const_cast<VARIANTARG *> (&x));
				};

				inline Variant::Variant(VARIANT_BOOL x)
				{
					VariantInit(&var_);
					var_.vt = VT_BOOL;
					var_.boolVal = x;
				};

				inline Variant::Variant(const VARIANT_BOOL *x)
				{
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_BOOL;
					var_.pboolVal = const_cast<VARIANT_BOOL *> (x);
				};

				inline Variant::Variant(const VARIANTARG *x)
				{
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_VARIANT;
					var_.pvarVal = const_cast<VARIANTARG *> (x);
				};

				inline Variant::Variant(unsigned long int x)
				{
					VariantInit(&var_);
					var_.vt = VT_UI4;
					var_.ulVal = x;
				};

				inline Variant::Variant(long int x)
				{
					VariantInit(&var_);
					var_.vt = VT_I4;
					var_.ulVal = x;
				};

				inline Variant::Variant(const LPSTR x)
				{
					BSTR theString;
					int length;

					length = MultiByteToWideChar(CP_ACP, 0, x, -1, 0, 0);
					theString = new wchar_t[length];
					MultiByteToWideChar(CP_ACP, 0, x, -1, theString, length);

					VariantInit(&var_);
					var_.vt = VT_BSTR;
					var_.bstrVal = SysAllocString(theString);
					delete[] theString;
				};

				inline Variant::Variant(const BSTR x)
				{
					VariantInit(&var_);
					var_.vt = VT_BSTR;
					var_.bstrVal = SysAllocString(x);
				};

				inline Variant::Variant(const IUnknown *x)
				{
					VariantInit(&var_);
					var_.vt = VT_UNKNOWN;
					var_.punkVal = const_cast<IUnknown *> (x);
					var_.punkVal->AddRef();
				};

				inline Variant::Variant(const IDispatch *x)
				{
					VariantInit(&var_);
					var_.vt = VT_DISPATCH;
					var_.pdispVal = const_cast<IDispatch *> (x);
					var_.pdispVal->AddRef();
				};

				inline Variant::Variant(const IUnknown **x)
				{
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_UNKNOWN;
					var_.ppunkVal = const_cast<IUnknown **> (x);
				};

				inline Variant::Variant(const IDispatch **x)
				{
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_DISPATCH;
					var_.ppdispVal = const_cast<IDispatch **> (x);
				};

				inline Variant &operator=(const VARIANTARG &x)
				{
					VariantClear(&var_);
					VariantCopy(&var_, const_cast<VARIANTARG *> (&x));
					return *this;
				};

				inline Variant &operator=(VARIANT_BOOL x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_BOOL;
					var_.boolVal = x;
					return *this;
				};

				inline Variant &operator=(const VARIANT_BOOL *x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_BOOL;
					var_.pboolVal = const_cast<VARIANT_BOOL *> (x);
					return *this;
				};

				inline Variant &operator=(const VARIANTARG *x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_VARIANT;
					var_.pvarVal = const_cast<VARIANTARG *> (x);
					return *this;
				};

				inline Variant &operator=(unsigned long int x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_UI4;
					var_.ulVal = x;
					return *this;
				};

				inline Variant &operator=(const LPSTR x)
				{
					BSTR theString;
					int length;

					length = MultiByteToWideChar(CP_ACP, 0, x, -1, 0, 0);
					theString = new wchar_t[length];
					MultiByteToWideChar(CP_ACP, 0, x, -1, theString, length);

					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_BSTR;
					var_.bstrVal = SysAllocString(theString);

					delete[] theString;
					return *this;
				};

				inline Variant &operator=(const BSTR x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_BSTR;
					var_.bstrVal = SysAllocString(x);
					return *this;
				};

				inline Variant &operator=(const IUnknown *x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_UNKNOWN;
					var_.punkVal = const_cast<IUnknown *> (x);
					var_.punkVal->AddRef();
					return *this;
				};

				inline Variant &operator=(const IDispatch *x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_DISPATCH;
					var_.pdispVal = const_cast<IDispatch *> (x);
					var_.pdispVal->AddRef();
					return *this;
				};

				inline Variant &operator=(const IUnknown **x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_UNKNOWN;
					var_.ppunkVal = const_cast<IUnknown **> (x);
					return *this;
				};

				inline Variant &operator=(const IDispatch **x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_BYREF | VT_DISPATCH;
					var_.ppdispVal = const_cast<IDispatch **> (x);
					return *this;
				};

				inline Variant &operator=(long int x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_I4;
					var_.lVal = x;
					return *this;
				};

				inline Variant &operator=(int x)
				{
					VariantClear(&var_);
					VariantInit(&var_);
					var_.vt = VT_INT;
					var_.intVal = x;
					return *this;
				};

				inline VARIANTARG *value()
				{
					return &var_;
				};

				inline operator VARIANT_BOOL ()
				{
					return var_.boolVal;
				};

				inline operator VARIANT_BOOL *()
				{
					return var_.pboolVal;
				};

				inline operator VARIANTARG *()
				{
					return var_.pvarVal;
				};

				inline operator unsigned long int()
				{
					return var_.ulVal;
				};

				inline operator long int()
				{
					return var_.lVal;
				};

				inline operator int()
				{
					return var_.intVal;
				};

				inline operator BSTR()
				{
					return var_.bstrVal;
				};

				inline operator IUnknown *()
				{
					return var_.punkVal;
				};

				inline operator IDispatch *()
				{
					return var_.pdispVal;
				};

				inline operator IUnknown **()
				{
					return var_.ppunkVal;
				};

				inline operator IDispatch **()
				{
					return var_.ppdispVal;
				};

		};

	};
};

#endif

