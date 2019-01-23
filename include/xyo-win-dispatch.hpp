//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_DISPATCH_HPP
#define XYO_WIN_DISPATCH_HPP

#ifndef XYO_WIN_DISPATCHVARIANT_HPP
#include "xyo-win-dispatchvariant.hpp"
#endif

#ifndef XYO_WIN_VARIANT_HPP
#include "xyo-win-variant.hpp"
#endif

namespace XYO {
	namespace Win {

		class Dispatch :
			public virtual Core::Object,
			public virtual ::IDispatch {
			protected:
				XYO_CORE_DISALLOW_COPY_ASSIGN_MOVE(Dispatch);
			public:
				inline Dispatch() {};
				inline ~Dispatch() {};

				//IUnknown
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID *ppvObj);
				XYO_WIN_EXPORT ULONG STDMETHODCALLTYPE AddRef();
				XYO_WIN_EXPORT ULONG STDMETHODCALLTYPE Release();

				//IDispatch
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT, LCID, LPTYPEINFO *);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID, LPOLESTR *, UINT, LCID, DISPID *);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);

				XYO_WIN_EXPORT virtual HRESULT invokeAndId(UINT mode, DISPID dispIdMember, DISPPARAMS *pDispParams, VARIANT *pVarResult, LPOLESTR *names, UINT count, DISPID *outID);

				XYO_WIN_EXPORT virtual void setDispatchFunctionsIdAndNames();
				XYO_WIN_EXPORT virtual ::IDispatch *getIDispatchValue();
		};

#define XYO_WIN_DISPATCH__PROTOTYPE \
	virtual HRESULT invokeAndId(UINT mode,DISPID dispIdMember,DISPPARAMS* pDispParams,VARIANT* pVarResult,LPOLESTR *names,UINT count,DISPID *outID)

#define XYO_WIN_DISPATCH__TABLE_BEGIN(XObject,StartId) \
	HRESULT XObject::invokeAndId(UINT mode,DISPID dispIdMember,DISPPARAMS* pDispParams,VARIANT* pVarResult,LPOLESTR *names,UINT count,DISPID *outID){\
		XYO::Win::Variant returnValue;\
		HRESULT id_returnValue;\
		UINT    id_count;\
		DISPID  id_func;\
		id_func=StartId;\
		id_returnValue=S_FALSE;\
		if(mode==1){\
			if(dispIdMember==0){\
				return (DISP_E_MEMBERNOTFOUND);\
			};\
		};\
		for(;;){



#define XYO_WIN_DISPATCH__TABLE_END(XBase) \
	break;\
};\
if(mode==0){\
	if(id_returnValue==S_FALSE){\
		return XBase::invokeAndId(mode,dispIdMember,pDispParams,pVarResult,names,count,outID);\
	};\
	return (id_returnValue);\
};\
if(mode==1){\
	if(id_func!=dispIdMember){\
		return XBase::invokeAndId(mode,dispIdMember,pDispParams,pVarResult,names,count,outID);\
	};\
	if(pVarResult!=NULL){\
		VariantCopyInd(pVarResult,returnValue.value());\
	};\
};\
return (S_OK);\
};


#define XYO_WIN_DISPATCH__TABLE_FUNCTION_0(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=0)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_1(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=1)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_2(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=2)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[1],&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_3(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=3)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[2],&pDispParams->rgvarg[1],&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_4(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=4)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[3],&pDispParams->rgvarg[2],&pDispParams->rgvarg[1],&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_5(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=5)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[4],&pDispParams->rgvarg[3],&pDispParams->rgvarg[2],&pDispParams->rgvarg[1],&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_6(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=6)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[5],&pDispParams->rgvarg[4],&pDispParams->rgvarg[3],&pDispParams->rgvarg[2],&pDispParams->rgvarg[1],&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_7(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=7)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[6],&pDispParams->rgvarg[5],&pDispParams->rgvarg[4],&pDispParams->rgvarg[3],&pDispParams->rgvarg[2],&pDispParams->rgvarg[1],&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func

#define XYO_WIN_DISPATCH__TABLE_FUNCTION_8(Function);\
	if(mode==0){\
		for(id_count=0;id_count<count;++id_count){\
			if(wcscmp(names[id_count],L#Function)==0){\
				outID[id_count]=id_func;\
				id_returnValue=S_OK;\
				break;\
			};\
		};\
	}else\
		if(mode==1){\
			if(id_func==dispIdMember){\
				if(pDispParams->cArgs!=8)return (DISP_E_BADPARAMCOUNT);\
				Function(returnValue,&pDispParams->rgvarg[7],&pDispParams->rgvarg[6],&pDispParams->rgvarg[5],&pDispParams->rgvarg[4],&pDispParams->rgvarg[3],&pDispParams->rgvarg[2],&pDispParams->rgvarg[1],&pDispParams->rgvarg[0]);\
				break;\
			};\
		};\
	++id_func


	};
};
#endif

