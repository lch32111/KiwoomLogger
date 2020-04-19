#include "KL/KLSystem.hpp"
#include <iostream>
#include <thread>

#include "KiwoomLoggerDlg.hpp"
#include "KW_OpenAPI.hpp"

#include "KL/KLScanner.hpp"

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
		KLScanner* scanner = new KLScanner();

		KLToken token;

		do
		{
			int r =	scanner->ScanToken(&token);
			if (r == 0)
			{
				std::wcout << token.string << _T('\n');
				continue;
			}

			switch (token.type)
			{
			case KL_TOKEN_PRINT_HELP:
			{
				break;
			}
			case KL_TOKEN_EOF:
			{
				break;
			}
			}
		} while (true);

		delete scanner;
	}
}

