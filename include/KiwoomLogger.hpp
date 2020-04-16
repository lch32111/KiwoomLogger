
#pragma once
#ifndef __KIWOOM_LOGGER_HPP__
#define __KIWOOM_LOGGER_HPP__

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "KW_OpenAPI.hpp"
#include "resource.h"

class KiwoomLoggerApp : public CWinApp
{
public:
	KiwoomLoggerApp();

	KW_OpenAPI m_kwOpenAPI;

	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern KiwoomLoggerApp theApp;
#endif