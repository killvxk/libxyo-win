//
// XYO Win Library
//
// Copyright (c) 2018-2019 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include <windows.h>
#include <ole2.h>
#include <shlobj.h>
#include <Shobjidl.h>
#include <docobj.h>
#include <mshtml.h>
#include <MsHtmHst.h>
#include <exdisp.h>
#include <exdispid.h>
#include <stdio.h>
#include <servprov.h>

#include "xyo-win-webbrowser.hpp"
#include "xyo-win-ole.hpp"
#include "xyo-win-variant.hpp"

namespace XYO {
	namespace Win {

		using namespace XYO;
		using namespace XYO::Core;

		WebBrowser::WebBrowser() {
			adviseCookie_ = 0;
			browser_ = NULL;
			connectionPoint_ = NULL;
			oleInPlaceActiveObject_ = NULL;
			browserDefaultAddress_="about:blank";
		};

		WebBrowser::~WebBrowser() {
		};

		// IUnknown

		HRESULT WebBrowser::QueryInterface(REFIID riid, LPVOID *ppvObj) {
			if (memcmp(&riid, &IID_IUnknown, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IStorage *> (this);
			} else if (memcmp(&riid, &IID_IStorage, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IStorage *> (this);
			} else if (memcmp(&riid, &IID_IOleClientSite, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IOleClientSite *> (this);
			} else if (memcmp(&riid, &IID_IOleInPlaceSite, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IOleInPlaceSite *> (this);
			} else if (memcmp(&riid, &IID_IOleInPlaceFrame, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IOleInPlaceFrame *> (this);
			} else if (memcmp(&riid, &IID_IDocHostUIHandler, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IDocHostUIHandler *> (this);
			} else if (memcmp(&riid, &DIID_DWebBrowserEvents2, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<DWebBrowserEvents2 *> (this);
			} else if (memcmp(&riid, &IID_IDispatch, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IDispatch *> (this);
			} else if (memcmp(&riid, &IID_IServiceProvider, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IServiceProvider *> (this);
			} else if (memcmp(&riid, &IID_IOleCommandTarget, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IOleCommandTarget *> (this);
			} else if (memcmp(&riid, &IID_IDropTarget, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IDropTarget *> (this);
			} else if (memcmp(&riid, &IID_IHttpSecurity, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IHttpSecurity *> (this);
			} else if (memcmp(&riid, &IID_IWindowForBindingUI, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IWindowForBindingUI *> (this);
			} else if (memcmp(&riid, &IID_INewWindowManager, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<INewWindowManager *> (this);
			} else if (memcmp(&riid, &IID_IAuthenticate, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IAuthenticate *> (this);
			} else if (memcmp(&riid, &IID_IInternetSecurityManager, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IInternetSecurityManager *> (this);
			} else if (memcmp(&riid, &IID_IProtectFocus, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IProtectFocus *> (this);
			} else if (memcmp(&riid, &IID_IHTMLOMWindowServices, sizeof (GUID)) == 0) {
				AddRef();
				*ppvObj = static_cast<IHTMLOMWindowServices *> (this);
			} else {
				*ppvObj = NULL;
				return (E_NOINTERFACE);
			}
			return (S_OK);
		};

		ULONG WebBrowser::AddRef() {
			return (ULONG)1;
		};

		ULONG WebBrowser::Release() {
			return (ULONG)1;
		};

		//IStorage

		HRESULT WebBrowser::CreateStream(const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm) {
			pwcsName;
			grfMode;
			reserved1;
			reserved2;
			ppstm;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::OpenStream(const WCHAR *pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm) {
			pwcsName;
			reserved1;
			grfMode;
			reserved2;
			ppstm;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::CreateStorage(const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg) {
			pwcsName;
			grfMode;
			reserved1;
			reserved2;
			ppstg;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::OpenStorage(const WCHAR *pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg) {
			pwcsName;
			pstgPriority;
			grfMode;
			snbExclude;
			reserved;
			ppstg;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::CopyTo(DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest) {
			ciidExclude;
			rgiidExclude;
			snbExclude;
			pstgDest;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::MoveElementTo(const OLECHAR *pwcsName, IStorage *pstgDest, const OLECHAR *pwcsNewName, DWORD grfFlags) {
			pwcsName;
			pstgDest;
			pwcsNewName;
			grfFlags;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::Commit(DWORD grfCommitFlags) {
			grfCommitFlags;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::Revert() {
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::EnumElements(DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenum) {
			reserved1;
			reserved2;
			reserved3;
			ppenum;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::DestroyElement(const OLECHAR *pwcsName) {
			pwcsName;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::RenameElement(const WCHAR *pwcsOldName, const WCHAR *pwcsNewName) {
			pwcsOldName;
			pwcsNewName;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::SetElementTimes(const WCHAR *pwcsName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime) {
			pwcsName;
			pctime;
			patime;
			pmtime;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::SetClass(REFCLSID clsid) {
			clsid;
			return (S_OK);
		};

		HRESULT WebBrowser::SetStateBits(DWORD grfStateBits, DWORD grfMask) {
			grfStateBits;
			grfMask;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::Stat(STATSTG *pstatstg, DWORD grfStatFlag) {
			pstatstg;
			grfStatFlag;
			return (E_NOTIMPL);
		};

		//IOleInPlaceFrame

		HRESULT WebBrowser::GetWindow(HWND FAR *lphwnd) {
			*lphwnd = *this;
			return (S_OK);
		};

		HRESULT WebBrowser::ContextSensitiveHelp(BOOL fEnterMode) {
			fEnterMode;
			return (S_OK);
		};

		HRESULT WebBrowser::GetBorder(LPRECT lprectBorder) {
			ZeroMemory(lprectBorder, sizeof (RECT));
			return (S_OK);
		};

		HRESULT WebBrowser::RequestBorderSpace(LPCBORDERWIDTHS pborderwidths) {
			pborderwidths;
			return (S_OK);
		};

		HRESULT WebBrowser::SetBorderSpace(LPCBORDERWIDTHS pborderwidths) {
			pborderwidths;
			return (S_OK);
		};

		HRESULT WebBrowser::SetActiveObject(IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName) {
			pActiveObject;
			pszObjName;
			return (S_OK);
		};

		HRESULT WebBrowser::InsertMenus(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths) {
			hmenuShared;
			lpMenuWidths;
			return (S_OK);
		};

		HRESULT WebBrowser::SetMenu(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject) {
			hmenuShared;
			holemenu;
			hwndActiveObject;
			return (S_OK);
		};

		HRESULT WebBrowser::RemoveMenus(HMENU hmenuShared) {
			hmenuShared;
			return (S_OK);
		};

		HRESULT WebBrowser::SetStatusText(LPCOLESTR pszStatusText) {
			pszStatusText;
			return (S_OK);
		};

		HRESULT WebBrowser::EnableModeless(BOOL fEnable) {
			fEnable;
			return (S_OK);
		};

		HRESULT WebBrowser::TranslateAccelerator(LPMSG lpmsg, WORD wID) {
			lpmsg;
			wID;
			return (S_FALSE);
		};

		//IOleClientSite

		HRESULT WebBrowser::SaveObject() {
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) {
			dwAssign;
			dwWhichMoniker;
			ppmk;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::GetContainer(LPOLECONTAINER FAR *ppContainer) {
			ppContainer;
			return (E_NOINTERFACE);
		};

		HRESULT WebBrowser::ShowObject() {
			return (NOERROR);
		};

		HRESULT WebBrowser::OnShowWindow(BOOL fShow) {
			fShow;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::RequestNewObjectLayout() {
			return (E_NOTIMPL);
		};

		//IOleInPlaceSite

		HRESULT WebBrowser::CanInPlaceActivate() {
			return (S_OK);
		};

		HRESULT WebBrowser::OnInPlaceActivate() {
			return (S_OK);
		};

		HRESULT WebBrowser::OnUIActivate() {
			return (S_OK);
		};

		HRESULT WebBrowser::GetWindowContext(LPOLEINPLACEFRAME FAR *lplpFrame, LPOLEINPLACEUIWINDOW FAR *lplpDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) {
			lprcPosRect;
			lprcClipRect;
			*lplpFrame = static_cast<LPOLEINPLACEFRAME> (this);
			*lplpDoc = 0;
			lpFrameInfo->fMDIApp = FALSE;
			lpFrameInfo->hwndFrame = *this;
			lpFrameInfo->haccel = 0;
			lpFrameInfo->cAccelEntries = 0;
			return (S_OK);
		};

		HRESULT WebBrowser::Scroll(SIZE scrollExtent) {
			scrollExtent;
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::OnUIDeactivate(BOOL fUndoable) {
			fUndoable;
			return (S_OK);
		};

		HRESULT WebBrowser::OnInPlaceDeactivate() {
			return (S_OK);
		};

		HRESULT WebBrowser::DiscardUndoState() {
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::DeactivateAndUndo() {
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::OnPosRectChange(LPCRECT lprcPosRect) {
			IOleInPlaceObject *inplace;
			if (!browser_->QueryInterface(IID_IOleInPlaceObject, (void **) &inplace)) {
				inplace->SetObjectRects(lprcPosRect, lprcPosRect);
				inplace->Release();
			};
			return (S_OK);
		};

		//IDocHostUIHandler

		HRESULT WebBrowser::ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved) {
			dwID;
			ppt;
			pcmdtReserved;
			pdispReserved;
			return (S_FALSE);
		};

		HRESULT WebBrowser::GetHostInfo(DOCHOSTUIINFO *pInfo) {
			pInfo->cbSize = sizeof (DOCHOSTUIINFO);
			pInfo->dwFlags = DOCHOSTUIFLAG_THEME;
			pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;
			return (S_OK);
		};

		HRESULT WebBrowser::ShowUI(DWORD dwID, IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc) {
			dwID;
			pActiveObject;
			pCommandTarget;
			pFrame;
			pDoc;
			return (S_OK);
		};

		HRESULT WebBrowser::HideUI() {
			return (S_OK);
		};

		HRESULT WebBrowser::UpdateUI() {
			return (S_OK);
		};

		HRESULT WebBrowser::OnDocWindowActivate(BOOL fActivate) {
			fActivate;
			return (S_OK);
		};

		HRESULT WebBrowser::OnFrameWindowActivate(BOOL fActivate) {
			fActivate;
			return (S_OK);
		};

		HRESULT WebBrowser::ResizeBorder(LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow) {
			prcBorder;
			pUIWindow;
			fRameWindow;
			return (S_OK);
		};

		HRESULT WebBrowser::TranslateAccelerator(LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID) {
			lpMsg;
			pguidCmdGroup;
			nCmdID;
			return (S_FALSE);
		};

		HRESULT WebBrowser::GetOptionKeyPath(LPOLESTR *pchKey, DWORD dw) {
			pchKey;
			dw;
			return (S_FALSE);
		};

		HRESULT WebBrowser::GetDropTarget(IDropTarget *pDropTarget, IDropTarget **ppDropTarget) {
			pDropTarget;
			ppDropTarget;
			return (S_FALSE);
		};

		HRESULT WebBrowser::GetExternal(IDispatch **ppDispatch) {
			*ppDispatch = (0);
			return (S_FALSE);
		};

		HRESULT WebBrowser::TranslateUrl(DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut) {
			dwTranslate;
			pchURLIn;
			ppchURLOut;
			*ppchURLOut = 0;
			return (S_FALSE);
		};

		HRESULT WebBrowser::FilterDataObject(IDataObject *pDO, IDataObject **ppDORet) {
			pDO;
			*ppDORet = 0;
			return (S_FALSE);
		};

		//IDocHostShowUI

		HRESULT WebBrowser::ShowHelp(HWND hwnd, LPOLESTR pszHelpFile, UINT uCommand, DWORD dwData, POINT ptMouse, IDispatch *pDispatchObjectHit) {
			hwnd;
			pszHelpFile;
			uCommand;
			dwData;
			ptMouse;
			pDispatchObjectHit;
			return (S_FALSE);
		};

		HRESULT WebBrowser::ShowMessage(HWND hwnd, LPOLESTR lpstrText, LPOLESTR lpstrCaption, DWORD dwType, LPOLESTR lpstrHelpFile, DWORD dwHelpContext, LRESULT *plResult) {
			hwnd;
			lpstrText;
			lpstrCaption;
			dwType;
			lpstrHelpFile;
			dwHelpContext;
			plResult;
			return (S_FALSE);
		};


		//DWebBrowserEvents2

		HRESULT WebBrowser::GetTypeInfoCount(UINT *) {
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::GetTypeInfo(UINT, LCID, LPTYPEINFO *) {
			return (E_NOTIMPL);
		};

		HRESULT WebBrowser::GetIDsOfNames(REFIID, LPOLESTR *names, UINT count, LCID, DISPID *outID) {
			names;
			count;
			outID;
			return (S_FALSE);
		};

		//IServiceProvider

		HRESULT WebBrowser::QueryService(REFGUID guidService, REFIID riid, void **ppv) {
			guidService;
			if (memcmp(&riid, &IID_IOleCommandTarget, sizeof (GUID) == 0)) {
				AddRef();
				*ppv = static_cast<IOleCommandTarget *> (this);
			} else {
				*ppv = NULL;
				return (E_NOINTERFACE);
			};
			return (S_OK);
		};

		//IOleCommandTarget

		HRESULT WebBrowser::QueryStatus(const GUID *pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[ ], OLECMDTEXT *pCmdText) {
			pguidCmdGroup;
			cCmds;
			prgCmds;
			pCmdText;
			return (OLECMDERR_E_UNKNOWNGROUP);
		};

		HRESULT WebBrowser::Exec(const GUID *pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt, VARIANT *pvaIn, VARIANT *pvaOut) {
			pguidCmdGroup;
			nCmdID;
			nCmdexecopt;
			pvaIn;
			pvaOut;
			return (OLECMDERR_E_UNKNOWNGROUP);
		};

		HRESULT WebBrowser::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr) {
			puArgErr;
			pExcepInfo;
			pVarResult;
			wFlags;
			lcid;
			riid;
			switch (dispIdMember) {
				case DISPID_BEFORENAVIGATE2:
					BeforeNavigate2(pDispParams->rgvarg[6].pdispVal, // pDisp
							pDispParams->rgvarg[5].pvarVal, // url
							pDispParams->rgvarg[4].pvarVal, // Flags
							pDispParams->rgvarg[3].pvarVal, // TargetFrameName
							pDispParams->rgvarg[2].pvarVal, // PostData
							pDispParams->rgvarg[1].pvarVal, // Headers
							pDispParams->rgvarg[0].pboolVal); // Cancel
					break;
				case DISPID_CLIENTTOHOSTWINDOW:
					ClientToHostWindow(pDispParams->rgvarg[1].plVal, pDispParams->rgvarg[0].plVal);
					break;
				case DISPID_COMMANDSTATECHANGE:
					CommandStateChange(pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_DOCUMENTCOMPLETE:
					DocumentComplete(pDispParams->rgvarg[1].pdispVal, pDispParams->rgvarg[0].pvarVal);
					break;
				case DISPID_DOWNLOADBEGIN:
					DownloadBegin();
					break;
				case DISPID_DOWNLOADCOMPLETE:
					DownloadComplete();
					break;
				case DISPID_FILEDOWNLOAD:
					FileDownload(pDispParams->rgvarg[0].pboolVal);
					break;
				case DISPID_NAVIGATECOMPLETE2:
					NavigateComplete(pDispParams->rgvarg[1].pdispVal, pDispParams->rgvarg[0].pvarVal);
					break;
				case DISPID_NAVIGATEERROR:
					NavigateError(pDispParams->rgvarg[4].pdispVal, pDispParams->rgvarg[3].pvarVal, pDispParams->rgvarg[2].pvarVal, pDispParams->rgvarg[1].pvarVal, pDispParams->rgvarg[0].pboolVal);
					break;
				case DISPID_NEWWINDOW2:
					NewWindow2(pDispParams->rgvarg[1].ppdispVal, pDispParams->rgvarg[0].pboolVal);
					break;
				case DISPID_ONFULLSCREEN:
					OnFullScreen(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_ONMENUBAR:
					OnMenuBar(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_ONQUIT:
					OnQuit();
					break;
				case DISPID_ONSTATUSBAR:
					OnStatusBar(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_ONTHEATERMODE:
					OnTheaterMode(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_ONTOOLBAR:
					OnToolBar(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_ONVISIBLE:
					OnVisible(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_PRINTTEMPLATEINSTANTIATION:
					PrintTemplateInstantiation(pDispParams->rgvarg[0].pdispVal);
					break;
				case DISPID_PRINTTEMPLATETEARDOWN:
					PrintTemplateTeardown(pDispParams->rgvarg[0].pdispVal);
					break;
				case DISPID_PRIVACYIMPACTEDSTATECHANGE:
					PrivacyImpactedStateChange(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_PROGRESSCHANGE:
					ProgressChange(pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
					break;
				case DISPID_PROPERTYCHANGE:
					PropertyChange(pDispParams->rgvarg[0].bstrVal);
					break;
				case DISPID_SETSECURELOCKICON:
					SetSecureLockIcon(pDispParams->rgvarg[0].lVal);
					break;
				case DISPID_STATUSTEXTCHANGE:
					StatusTextChange(pDispParams->rgvarg[0].bstrVal);
					break;
				case DISPID_TITLECHANGE:
					TitleChange(pDispParams->rgvarg[0].bstrVal);
					break;
				case DISPID_WINDOWCLOSING:
					WindowClosing(pDispParams->rgvarg[1].boolVal, pDispParams->rgvarg[0].pboolVal);
					break;
				case DISPID_WINDOWSETHEIGHT:
					WindowSetHeight(pDispParams->rgvarg[0].lVal);
					break;
				case DISPID_WINDOWSETLEFT:
					WindowSetLeft(pDispParams->rgvarg[0].lVal);
					break;
				case DISPID_WINDOWSETRESIZABLE:
					WindowSetResizable(pDispParams->rgvarg[0].boolVal);
					break;
				case DISPID_WINDOWSETTOP:
					WindowSetTop(pDispParams->rgvarg[0].lVal);
					break;
				case DISPID_WINDOWSETWIDTH:
					WindowSetWidth(pDispParams->rgvarg[0].lVal);
					break;
				default:
					return DISP_E_MEMBERNOTFOUND;
			};
			return (S_OK);
		};

		void WebBrowser::StatusTextChange(BSTR) {
		};

		void WebBrowser::ProgressChange(long, long) {
		};

		void WebBrowser::CommandStateChange(long, VARIANT_BOOL) {
		};

		void WebBrowser::DownloadBegin() {
		};

		void WebBrowser::DownloadComplete() {
		};

		void WebBrowser::TitleChange(BSTR) {
		};

		void WebBrowser::PropertyChange(BSTR) {
		};

		void WebBrowser::BeforeNavigate2(IDispatch *, VARIANT *, VARIANT *, VARIANT *, VARIANT *, VARIANT *, VARIANT_BOOL *) {
		};

		void WebBrowser::NewWindow2(IDispatch **, VARIANT_BOOL *) {
		};

		void WebBrowser::NavigateComplete(IDispatch *, VARIANT *) {
		};

		void WebBrowser::NavigateError(IDispatch *, VARIANT *, VARIANT *, VARIANT *, VARIANT_BOOL *) {
		};

		void WebBrowser::DocumentComplete(IDispatch *, VARIANT *) {
		};

		void WebBrowser::OnQuit() {
			PostMessage(*this, WM_CLOSE, 0, 0);
		};

		void WebBrowser::OnVisible(VARIANT_BOOL) {
		};

		void WebBrowser::OnToolBar(VARIANT_BOOL) {
		};

		void WebBrowser::OnMenuBar(VARIANT_BOOL) {
		};

		void WebBrowser::OnStatusBar(VARIANT_BOOL) {
		};

		void WebBrowser::OnFullScreen(VARIANT_BOOL) {
		};

		void WebBrowser::OnTheaterMode(VARIANT_BOOL) {
		};

		void WebBrowser::WindowSetResizable(VARIANT_BOOL) {
		};

		void WebBrowser::WindowSetLeft(long Value) {
			Value;
		};

		void WebBrowser::WindowSetTop(long Value) {
			Value;
		};

		void WebBrowser::WindowSetWidth(long Value) {
			Value;
		};

		void WebBrowser::WindowSetHeight(long Value) {
			Value;
		};

		void WebBrowser::WindowClosing(VARIANT_BOOL isChild, VARIANT_BOOL *allow) {
			isChild;
			*allow = VARIANT_TRUE;
			PostMessage(*this, WM_CLOSE, 0, 0);
		};

		void WebBrowser::ClientToHostWindow(long *x, long *y) {
			x,y;
		};

		void WebBrowser::SetSecureLockIcon(long x) {
			x;
		};

		void WebBrowser::FileDownload(VARIANT_BOOL *x) {
			x;
		};

		void WebBrowser::PrintTemplateInstantiation(IDispatch *x) {
			x;
		};

		void WebBrowser::PrintTemplateTeardown(IDispatch *x) {
			x;
		};

		void WebBrowser::PrivacyImpactedStateChange(VARIANT_BOOL x) {
			x;
		};


		//IDropTarget
		HRESULT STDMETHODCALLTYPE WebBrowser::DragEnter(IDataObject *pDataObj,DWORD grfKeyState,POINTL pt,DWORD *pdwEffect) {
			pDataObj,grfKeyState,pt,pdwEffect;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::DragOver(DWORD grfKeyState,POINTL pt,DWORD *pdwEffect) {
			grfKeyState,pt,pdwEffect;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::DragLeave(void) {
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::Drop(IDataObject *pDataObj,DWORD grfKeyState,POINTL pt,DWORD *pdwEffect) {
			pDataObj,grfKeyState,pt,pdwEffect;
			return (E_NOTIMPL);
		};

		//IHttpSecurity
		HRESULT STDMETHODCALLTYPE WebBrowser::OnSecurityProblem(DWORD dwProblem) {
			dwProblem;
			return (E_NOTIMPL);
		};

		//IWindowForBindingUI
		HRESULT STDMETHODCALLTYPE WebBrowser::GetWindow(REFGUID rguidReason,HWND *phwnd) {
			rguidReason,phwnd;
			return (E_NOTIMPL);
		};

		//INewWindowManager
		HRESULT STDMETHODCALLTYPE WebBrowser::EvaluateNewWindow(LPCWSTR pszUrl,LPCWSTR pszName,LPCWSTR pszUrlContext,LPCWSTR pszFeatures,BOOL fReplace,DWORD dwFlags,DWORD dwUserActionTime) {
			pszUrl,pszName,pszUrlContext,pszFeatures,fReplace,dwFlags,dwUserActionTime;
			return (E_NOTIMPL);
		};

		//IAuthenticate
		HRESULT STDMETHODCALLTYPE WebBrowser::Authenticate(HWND *phwnd,LPWSTR *pszUsername,LPWSTR *pszPassword) {
			phwnd,pszUsername,pszPassword;
			return (E_NOTIMPL);
		};

		//IInternetSecurityManager
		HRESULT STDMETHODCALLTYPE WebBrowser::SetSecuritySite(IInternetSecurityMgrSite *pSite) {
			pSite;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::GetSecuritySite(IInternetSecurityMgrSite **ppSite) {
			ppSite;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::MapUrlToZone(LPCWSTR pwszUrl,DWORD *pdwZone,DWORD dwFlags) {
			pwszUrl,pdwZone,dwFlags;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::GetSecurityId(LPCWSTR pwszUrl,BYTE *pbSecurityId,DWORD *pcbSecurityId,DWORD_PTR dwReserved) {
			pwszUrl,pbSecurityId,pcbSecurityId,dwReserved;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::ProcessUrlAction(LPCWSTR pwszUrl,DWORD dwAction,BYTE *pPolicy,DWORD cbPolicy,BYTE *pContext,DWORD cbContext,DWORD dwFlags,DWORD dwReserved) {
			pwszUrl,dwAction,pPolicy,cbPolicy,pContext,cbContext,dwFlags,dwReserved;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::QueryCustomPolicy(LPCWSTR pwszUrl,REFGUID guidKey,BYTE **ppPolicy,DWORD *pcbPolicy,BYTE *pContext,DWORD cbContext,DWORD dwReserved) {
			pwszUrl,guidKey,ppPolicy,pcbPolicy,pContext,cbContext,dwReserved;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::SetZoneMapping(DWORD dwZone,LPCWSTR lpszPattern,DWORD dwFlags) {
			dwZone,lpszPattern,dwFlags;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::GetZoneMappings(DWORD dwZone,IEnumString **ppenumString,DWORD dwFlags) {
			dwZone,ppenumString,dwFlags;
			return (E_NOTIMPL);
		};

		//IProtectFocus
		HRESULT STDMETHODCALLTYPE WebBrowser::AllowFocusChange(BOOL *pfAllow) {
			pfAllow;
			return (E_NOTIMPL);
		};

		//IHTMLOMWindowServices
		HRESULT STDMETHODCALLTYPE WebBrowser::moveTo(LONG x,LONG y) {
			x,y;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::moveBy(LONG x,LONG y) {
			x,y;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::resizeTo(LONG x,LONG y) {
			x,y;
			return (E_NOTIMPL);
		};

		HRESULT STDMETHODCALLTYPE WebBrowser::resizeBy(LONG x,LONG y) {
			x,y;
			return (E_NOTIMPL);
		};

		int WebBrowser::connectObject() {
			IWebBrowser2 *webBrowser2;
			IConnectionPointContainer *conPtCon;
			RECT rect;
			int retVal;

			adviseCookie_ = 0;
			retVal = 0;

			if (!Ole::isValid()) {
				return 0;
			};

			releaseObject();

			if (OleCreate(CLSID_WebBrowser, IID_IOleObject, OLERENDER_DRAW, 0, (IOleClientSite *)this, (IStorage *)this, (void **) &browser_) == S_OK) {
				browser_->SetHostNames(L"Microsoft Internet Explorer", 0);
				GetClientRect(*this, &rect);
				browser_->AddRef();
				if (!OleSetContainedObject((struct IUnknown *) browser_, TRUE)) {
					if (!browser_->DoVerb(OLEIVERB_SHOW, NULL, (IOleClientSite *)this, -1, *this, &rect)) {
						if (!browser_->QueryInterface(IID_IWebBrowser2, (void **) &webBrowser2)) {
							if (!webBrowser2->QueryInterface(IID_IConnectionPointContainer, (void **) &conPtCon)) {
								if (!conPtCon->FindConnectionPoint(DIID_DWebBrowserEvents2, &connectionPoint_)) {
									connectionPoint_->Advise((DWebBrowserEvents2 *)this, &adviseCookie_);
									retVal = 1;
								};
								conPtCon->Release();
							};

							if (browser_->QueryInterface(IID_IOleInPlaceActiveObject, (void **) &oleInPlaceActiveObject_) != S_OK) {
								oleInPlaceActiveObject_ = NULL;
							};

							webBrowser2->Release();
						};
					};
				};
				if (retVal == 0) {
					browser_->Close(OLECLOSE_NOSAVE);
					browser_->Release();
					browser_ = NULL;
				};
			};
			return retVal;
		};

		int WebBrowser::releaseObject() {
			if (oleInPlaceActiveObject_ != NULL) {
				oleInPlaceActiveObject_->Release();
				oleInPlaceActiveObject_ = NULL;
			};
			if (connectionPoint_ != NULL) {
				connectionPoint_->Unadvise(adviseCookie_);
				connectionPoint_->Release();
				connectionPoint_ = NULL;
			};
			if (browser_ != NULL) {
				browser_->Close(OLECLOSE_NOSAVE);
				browser_->Release();
				browser_ = NULL;
			};
			return 1;
		};

		LRESULT WebBrowser::windowProcedure(UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case WM_CREATE:
					if (!connectObject()) {
						return -1L;
					}
					PostMessage(*this,WUM_BROWSER_DO_NAVIGATE1,0,0);
					break;
				case WUM_BROWSER_DO_NAVIGATE1: {
						Navigate("about:blank");
						PostMessage(*this,WUM_BROWSER_DO_NAVIGATE2,0,0);
						return 0L;
					};
				case WUM_BROWSER_DO_NAVIGATE2: {
						Navigate(browserDefaultAddress_);
						return 0L;
					};
				case WM_CLOSE:
					DestroyWindow(*this);
					break;
				case WM_DESTROY:
					releaseObject();
					break;
				case WM_SIZE: {
						::IWebBrowser2 *iWebBrowser2_;
						if (!browser_->QueryInterface(IID_IWebBrowser2, (void **) &iWebBrowser2_)) {
							iWebBrowser2_->put_Width(LOWORD(lParam));
							iWebBrowser2_->put_Height(HIWORD(lParam));
							iWebBrowser2_->Release();
						};
					};
					break;
				default:
					return Window::windowProcedure(uMsg, wParam, lParam);
			};
			return 0L;
		};

		bool WebBrowser::translateAccelerator(MSG &msg) {
			if(oleInPlaceActiveObject_ == NULL) {
				return false;
			};
			if(msg.hwnd==*this||IsChild(*this,msg.hwnd)) {
				if (oleInPlaceActiveObject_->TranslateAccelerator(&msg) == S_OK) {
					return true;
				};
			};
			return false;
		};

		int WebBrowser::Navigate(String url) {
			IWebBrowser2 *WebBrowser2;
			VARIANT myURL;

			if (browser_ == NULL) {
				return 0;
			}

			if (!browser_->QueryInterface(IID_IWebBrowser2, (void **) &WebBrowser2)) {

				size_t newSize = url.length() + 1;
				wchar_t *url_ = new wchar_t[newSize];
				size_t convertedChars = 0;
				mbstowcs_s(&convertedChars, url_, newSize, url, _TRUNCATE);
				VariantInit(&myURL);
				myURL.vt = VT_BSTR;
				myURL.bstrVal = SysAllocString((BSTR) url_);
				delete url_;

				WebBrowser2->Navigate2(&myURL, 0, 0, 0, 0);

				VariantClear(&myURL);
				WebBrowser2->Release();
				return 1;

			}
			return 0;
		};

	};
};

