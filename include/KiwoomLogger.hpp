
// KiwoomLogger.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "KW_OpenAPI.hpp"
#include "resource.h"		// main symbols

class KiwoomLoggerApp : public CWinApp
{
public:
	KiwoomLoggerApp();

	KW_OpenAPI m_kwOpenAPI;

	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern KiwoomLoggerApp theApp;
