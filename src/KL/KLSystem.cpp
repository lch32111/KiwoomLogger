#include "KL/KLSystem.hpp"
#include <iostream>
#include <thread>

#include "KiwoomLoggerDlg.hpp"
#include "KW_OpenAPI.hpp"

KiwoomLoggerDlg* KLDLG;
KW_OpenAPI* KWAPI;

namespace KiwoomLogger
{
	void enterInternal();

	void EnterKLSystem(KiwoomLoggerDlg* dlg, KW_OpenAPI* kw)
	{
		KLDLG = dlg;
		KWAPI = kw;
		std::wcout << _T("Kiwoom Open API 로그인 성공\n");
		std::thread thread(enterInternal);
		thread.detach();
	}

	void enterInternal()
	{
		CString input;
		CString tempBuffer;

		while (std::wcin >> input.GetBuffer())
		{
			std::wcout << _T("Input : ") << input.GetString() << _T('\n');

			if (input == _T("exit"))
			{
				INT_PTR a = 0;
				EndDialog(KLDLG->GetSafeHwnd(), a);
			}
			else if (input == _T("list"))
			{
				KWAPI->GetCodeListByMarket(tempBuffer, _T("10"));
				std::wcout << tempBuffer.GetString() << _T('\n');
			}
		}
	}
}

