//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_WIN_WEBBROWSER_HPP
#define XYO_WIN_WEBBROWSER_HPP

#ifndef XYO_WIN_WINDOW_HPP
#include "xyo-win-window.hpp"
#endif

#define WUM_BROWSER_DO_NAVIGATE1 (WM_USER+2000)
#define WUM_BROWSER_DO_NAVIGATE2 (WM_USER+2001)

namespace XYO {
	namespace Win {

		class WebBrowser :
			public virtual Window,
			public virtual ::IStorage,
			public virtual ::IOleInPlaceFrame,
			public virtual ::IOleClientSite,
			public virtual ::IOleInPlaceSite,
			public virtual ::IOleCommandTarget,
			public virtual ::IDocHostUIHandler,
			public virtual ::IDocHostShowUI,
			public virtual ::IServiceProvider,
			public virtual ::DWebBrowserEvents2,
			public virtual ::IDropTarget,
			public virtual ::IHttpSecurity,
			public virtual ::IWindowForBindingUI,
			public virtual ::INewWindowManager,
			public virtual ::IAuthenticate,
			public virtual ::IInternetSecurityManager,
			public virtual ::IProtectFocus,
			public virtual ::IHTMLOMWindowServices {
				XYO_CORE_DISALLOW_COPY_ASSIGN_MOVE(WebBrowser);
			protected:
				IOleObject *browser_;
				DWORD adviseCookie_;
				IConnectionPoint *connectionPoint_;
				IOleInPlaceActiveObject *oleInPlaceActiveObject_;

				XYO_WIN_EXPORT int connectObject();
				XYO_WIN_EXPORT int releaseObject();

				XYO::Core::String browserDefaultAddress_;
			public:

				XYO_WIN_EXPORT WebBrowser();
				XYO_WIN_EXPORT ~WebBrowser();

				XYO_WIN_EXPORT LRESULT windowProcedure(UINT uMsg, WPARAM wParam, LPARAM lParam);
				XYO_WIN_EXPORT bool translateAccelerator(MSG &msg);

				//IUnknown
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID *ppvObj);
				XYO_WIN_EXPORT ULONG STDMETHODCALLTYPE AddRef();
				XYO_WIN_EXPORT ULONG STDMETHODCALLTYPE Release();

				//IStorage
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE CreateStream(const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStream **ppstm);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OpenStream(const WCHAR *pwcsName, void *reserved1, DWORD grfMode, DWORD reserved2, IStream **ppstm);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE CreateStorage(const WCHAR *pwcsName, DWORD grfMode, DWORD reserved1, DWORD reserved2, IStorage **ppstg);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OpenStorage(const WCHAR *pwcsName, IStorage *pstgPriority, DWORD grfMode, SNB snbExclude, DWORD reserved, IStorage **ppstg);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE CopyTo(DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, IStorage *pstgDest);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE MoveElementTo(const OLECHAR *pwcsName, IStorage *pstgDest, const OLECHAR *pwcsNewName, DWORD grfFlags);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Commit(DWORD grfCommitFlags);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Revert();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE EnumElements(DWORD reserved1, void *reserved2, DWORD reserved3, IEnumSTATSTG **ppenum);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE DestroyElement(const OLECHAR *pwcsName);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE RenameElement(const WCHAR *pwcsOldName, const WCHAR *pwcsNewName);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetElementTimes(const WCHAR *pwcsName, FILETIME const *pctime, FILETIME const *patime, FILETIME const *pmtime);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetClass(REFCLSID clsid);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetStateBits(DWORD grfStateBits, DWORD grfMask);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Stat(STATSTG *pstatstg, DWORD grfStatFlag);

				//IOleInPlaceFrame
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetWindow(HWND FAR *lphwnd);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetBorder(LPRECT lprectBorder);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE RequestBorderSpace(LPCBORDERWIDTHS pborderwidths);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetBorderSpace(LPCBORDERWIDTHS pborderwidths);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetActiveObject(IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE InsertMenus(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetMenu(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE RemoveMenus(HMENU hmenuShared);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetStatusText(LPCOLESTR pszStatusText);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpmsg, WORD wID);

				//IOleClientSite
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SaveObject();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetContainer(LPOLECONTAINER FAR *ppContainer);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ShowObject();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnShowWindow(BOOL fShow);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE RequestNewObjectLayout();

				//IOleInPlaceSite
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE CanInPlaceActivate();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnInPlaceActivate();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnUIActivate();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetWindowContext(LPOLEINPLACEFRAME FAR *lplpFrame, LPOLEINPLACEUIWINDOW FAR *lplpDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Scroll(SIZE scrollExtent);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE DiscardUndoState();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE DeactivateAndUndo();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect);

				//IOleCommandTarget
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE QueryStatus(const GUID *pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[], OLECMDTEXT *pCmdText);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Exec(const GUID *pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt, VARIANT *pvaIn, VARIANT *pvaOut);


				//IDocHostUIHandler
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO *pInfo);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ShowUI(DWORD dwID, IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE HideUI();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE UpdateUI();
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL fActivate);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL fActivate);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ResizeBorder(LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetOptionKeyPath(LPOLESTR *pchKey, DWORD dw);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetDropTarget(IDropTarget *pDropTarget, IDropTarget **ppDropTarget);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetExternal(IDispatch **ppDispatch);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE TranslateUrl(DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE FilterDataObject(IDataObject *pDO, IDataObject **ppDORet);

				//IDocHostShowUI
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ShowHelp(HWND hwnd, LPOLESTR pszHelpFile, UINT uCommand, DWORD dwData, POINT ptMouse, IDispatch *pDispatchObjectHit);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ShowMessage(HWND hwnd, LPOLESTR lpstrText, LPOLESTR lpstrCaption, DWORD dwType, LPOLESTR lpstrHelpFile, DWORD dwHelpContext, LRESULT *plResult);

				//IServiceProvider
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE QueryService(REFGUID guidService, REFIID riid, void **ppv);

				//DWebBrowserEvents2
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT, LCID, LPTYPEINFO *);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID, LPOLESTR *, UINT, LCID, DISPID *);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);

				//DWebBrowserEvents2
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE StatusTextChange(BSTR);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE ProgressChange(long, long);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE CommandStateChange(long, VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE DownloadBegin();
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE DownloadComplete();
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE TitleChange(BSTR);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE PropertyChange(BSTR);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE BeforeNavigate2(IDispatch *, VARIANT *, VARIANT *, VARIANT *, VARIANT *, VARIANT *, VARIANT_BOOL *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE NewWindow2(IDispatch **, VARIANT_BOOL *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE NavigateComplete(IDispatch *, VARIANT *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE NavigateError(IDispatch *, VARIANT *, VARIANT *, VARIANT *, VARIANT_BOOL *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE DocumentComplete(IDispatch *, VARIANT *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE OnQuit();
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE OnVisible(VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE OnToolBar(VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE OnMenuBar(VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE OnStatusBar(VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE OnFullScreen(VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE OnTheaterMode(VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE WindowSetResizable(VARIANT_BOOL);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE WindowSetLeft(long);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE WindowSetTop(long);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE WindowSetWidth(long);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE WindowSetHeight(long);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE WindowClosing(VARIANT_BOOL, VARIANT_BOOL *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE ClientToHostWindow(long *, long *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE SetSecureLockIcon(long);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE FileDownload(VARIANT_BOOL *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE PrintTemplateInstantiation(IDispatch *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE PrintTemplateTeardown(IDispatch *);
				XYO_WIN_EXPORT virtual void STDMETHODCALLTYPE PrivacyImpactedStateChange(VARIANT_BOOL);

				//IDropTarget
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE DragEnter(IDataObject *pDataObj,DWORD grfKeyState,POINTL pt,DWORD *pdwEffect);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState,POINTL pt,DWORD *pdwEffect);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE DragLeave(void);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Drop(IDataObject *pDataObj,DWORD grfKeyState,POINTL pt,DWORD *pdwEffect);

				//IHttpSecurity
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE OnSecurityProblem(DWORD dwProblem);

				//IWindowForBindingUI
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetWindow(REFGUID rguidReason,HWND *phwnd);

				//INewWindowManager
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE EvaluateNewWindow(LPCWSTR pszUrl,LPCWSTR pszName,LPCWSTR pszUrlContext,LPCWSTR pszFeatures,BOOL fReplace,DWORD dwFlags,DWORD dwUserActionTime);

				//IAuthenticate
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE Authenticate(HWND *phwnd,LPWSTR *pszUsername,LPWSTR *pszPassword);

				//IInternetSecurityManager
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetSecuritySite(IInternetSecurityMgrSite *pSite);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetSecuritySite(IInternetSecurityMgrSite **ppSite);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE MapUrlToZone(LPCWSTR pwszUrl,DWORD *pdwZone,DWORD dwFlags);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetSecurityId(LPCWSTR pwszUrl,BYTE *pbSecurityId,DWORD *pcbSecurityId,DWORD_PTR dwReserved);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE ProcessUrlAction(LPCWSTR pwszUrl,DWORD dwAction,BYTE *pPolicy,DWORD cbPolicy,BYTE *pContext,DWORD cbContext,DWORD dwFlags,DWORD dwReserved);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE QueryCustomPolicy(LPCWSTR pwszUrl,REFGUID guidKey,BYTE **ppPolicy,DWORD *pcbPolicy,BYTE *pContext,DWORD cbContext,DWORD dwReserved);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE SetZoneMapping(DWORD dwZone,LPCWSTR lpszPattern,DWORD dwFlags);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE GetZoneMappings(DWORD dwZone,IEnumString **ppenumString,DWORD dwFlags);

				//IProtectFocus
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE AllowFocusChange(BOOL *pfAllow);

				//IHTMLOMWindowServices
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE moveTo(LONG x,LONG y);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE moveBy(LONG x,LONG y);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE resizeTo(LONG x,LONG y);
				XYO_WIN_EXPORT HRESULT STDMETHODCALLTYPE resizeBy(LONG x,LONG y);

				//Browser
				XYO_WIN_EXPORT int Navigate(Core::String url);


		};

	};
};

#endif

