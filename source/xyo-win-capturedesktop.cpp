//
// XYO Win Library
//
// Copyright (c) 2018 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include <windows.h>
#include <stdio.h>

#include "xyo-win-capturedesktop.hpp"
#include "libxyo-pixel32.hpp"

namespace XYO {
	namespace Win {

		using namespace XYO::Core;
		using namespace XYO::Pixel32;

		class MonitorInfo:
			public Object {
				XYO_CORE_DISALLOW_COPY_ASSIGN_MOVE(MonitorInfo);
			public:
				HDC hdc;
				RECT rect;

				inline MonitorInfo() {
					hdc=NULL;
					memset(&rect,0,sizeof(RECT));
				};

				inline ~MonitorInfo() {
					if(hdc!=NULL) {
						DeleteDC(hdc);
					};
				};
		};

		static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData) {
			TDynamicArray<MonitorInfo,4,TMemorySystem> *monitorInfo=reinterpret_cast<TDynamicArray<MonitorInfo,4,TMemorySystem> *>(dwData);

			HDC hdcMonitorCopy=CreateCompatibleDC(hdcMonitor);
			if(hdcMonitorCopy) {
				int monitorWidth=GetDeviceCaps(hdcMonitor,HORZRES);
				int monitorHeight=GetDeviceCaps(hdcMonitor,VERTRES);
				HBITMAP bmpMonitor=CreateCompatibleBitmap(hdcMonitor,monitorWidth,monitorHeight);
				if(bmpMonitor) {
					HBITMAP bmpMonitorOld=(HBITMAP)SelectObject(hdcMonitorCopy,bmpMonitor);
					if(bmpMonitorOld) {
						if(BitBlt(hdcMonitorCopy,0,0,monitorWidth,monitorHeight,hdcMonitor,lprcMonitor->left,lprcMonitor->top,SRCCOPY|CAPTUREBLT)) {

							int index_=monitorInfo->length();
							(monitorInfo->index(index_)).hdc=hdcMonitorCopy;
							(monitorInfo->index(index_)).rect=*lprcMonitor;

							DeleteDC(hdcMonitor);
							DeleteObject(bmpMonitor);

							return TRUE;
						};
						DeleteObject(bmpMonitorOld);
					};
					DeleteObject(bmpMonitor);
				};
				DeleteDC(hdcMonitorCopy);
			};

			DeleteDC(hdcMonitor);
			return TRUE;
		};

		bool CaptureDesktop::captureDesktopToPNGFile(char *fileName) {
			HDC hdcDesktop;
			HDC hdcCapture;
			HBITMAP bmpCapture;
			HBITMAP bmpCaptureOld;
			TDynamicArray<MonitorInfo,4,TMemorySystem> monitorInfo;
			int screenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
			int minLeft=0;
			int minTop=0;
			int k;

			hdcDesktop=GetDC(NULL);
			if(hdcDesktop==NULL) {
				return false;
			};

			hdcCapture = CreateCompatibleDC(hdcDesktop);
			if(hdcCapture==NULL) {
				DeleteDC(hdcDesktop);
				return false;
			};

			bmpCapture=CreateCompatibleBitmap(hdcDesktop, screenWidth, screenHeight);
			if(bmpCapture==NULL) {
				DeleteDC(hdcDesktop);
				DeleteDC(hdcCapture);
				return false;
			};

			bmpCaptureOld=(HBITMAP)SelectObject(hdcCapture, bmpCapture);
			if(bmpCaptureOld==NULL) {
				DeleteDC(hdcDesktop);
				DeleteDC(hdcCapture);
				DeleteObject(bmpCapture);
				return false;
			};

			if(!EnumDisplayMonitors(hdcDesktop, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(&monitorInfo))) {
				SelectObject(hdcCapture,bmpCaptureOld);
				DeleteDC(hdcDesktop);
				DeleteDC(hdcCapture);
				DeleteObject(bmpCapture);
				return false;
			};

			for(k=0; k<monitorInfo.length(); ++k) {
				if(monitorInfo[k].rect.left<minLeft) {
					minLeft=monitorInfo[k].rect.left;
				};
				if(monitorInfo[k].rect.top<minTop) {
					minTop=monitorInfo[k].rect.top;
				};
			};

			for(k=0; k<monitorInfo.length(); ++k) {
				if(!BitBlt(hdcCapture,monitorInfo[k].rect.left-minLeft,monitorInfo[k].rect.top-minTop,monitorInfo[k].rect.right-monitorInfo[k].rect.left,monitorInfo[k].rect.bottom-monitorInfo[k].rect.top,monitorInfo[k].hdc,0,0,SRCCOPY)) {
					SelectObject(hdcCapture,bmpCaptureOld);
					DeleteDC(hdcDesktop);
					DeleteDC(hdcCapture);
					DeleteObject(bmpCapture);
					return false;
				};
			};

			SelectObject(hdcCapture,bmpCaptureOld);

			uint8_t *imageBI=new uint8_t[sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)];
			memset(imageBI,0,sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD));
			((LPBITMAPINFO)imageBI)->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
			((LPBITMAPINFO)imageBI)->bmiHeader.biHeight=screenHeight;
			((LPBITMAPINFO)imageBI)->bmiHeader.biWidth=screenWidth;
			((LPBITMAPINFO)imageBI)->bmiHeader.biPlanes=1;
			((LPBITMAPINFO)imageBI)->bmiHeader.biBitCount=32;
			((LPBITMAPINFO)imageBI)->bmiHeader.biCompression=BI_RGB;
			if(!GetDIBits(hdcCapture,bmpCapture,0,screenHeight,NULL,(LPBITMAPINFO)imageBI,DIB_RGB_COLORS)) {
				DeleteDC(hdcDesktop);
				DeleteDC(hdcCapture);
				DeleteObject(bmpCapture);
				return false;
			};

			if(((LPBITMAPINFO)imageBI)->bmiHeader.biCompression!=BI_RGB) {
				DeleteDC(hdcDesktop);
				DeleteDC(hdcCapture);
				DeleteObject(bmpCapture);
				delete imageBI;
				return false;
			};

			DWORD imageSize=((LPBITMAPINFO)imageBI)->bmiHeader.biSizeImage;
			DWORD imageBits=(((LPBITMAPINFO)imageBI)->bmiHeader.biPlanes)*(((LPBITMAPINFO)imageBI)->bmiHeader.biBitCount);
			DWORD palSize=0;
			switch(imageBits) {
				case 1:
					palSize=2;
					break;
				case 4:
					palSize=16;
					break;
				case 8:
					palSize=256;
					break;
			};
			DWORD imageFileSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+palSize*sizeof(RGBQUAD)+imageSize;
			uint8_t *imageFile=new uint8_t[imageFileSize];
			memset(imageFile,0,imageFileSize);
			((BITMAPFILEHEADER *)imageFile)->bfType=XYO_PIXEL32_BMP_FILE_ID;
			((BITMAPFILEHEADER *)imageFile)->bfReserved1=0;
			((BITMAPFILEHEADER *)imageFile)->bfReserved2=0;
			((BITMAPFILEHEADER *)imageFile)->bfSize=imageSize;
			((BITMAPFILEHEADER *)imageFile)->bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+palSize*sizeof(RGBQUAD);
			memcpy((((BITMAPFILEHEADER *)imageFile)+1),imageBI,sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD));

			if(!GetDIBits(hdcCapture,bmpCapture,0,screenHeight,&imageFile[((BITMAPFILEHEADER *)imageFile)->bfOffBits],(LPBITMAPINFO)imageBI,DIB_RGB_COLORS)) {
				DeleteDC(hdcDesktop);
				DeleteDC(hdcCapture);
				DeleteObject(bmpCapture);
				delete imageBI;
				delete imageFile;
				return false;
			};

			TPointer<Bmp> image=Bmp::newImageOwner((BmpImage *)imageFile);
			TPointer<Bmp> image2=image->convertTo32Bits();
			image2->setAlpha32(0);
			if(Process::bmp32SavePng(image2,fileName)) {
				DeleteDC(hdcDesktop);
				DeleteDC(hdcCapture);
				DeleteObject(bmpCapture);
				delete imageBI;
				return true;
			};

			DeleteDC(hdcDesktop);
			DeleteDC(hdcCapture);
			DeleteObject(bmpCapture);
			delete imageBI;

			return false;
		};

	};
};

