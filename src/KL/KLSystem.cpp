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

	std::vector<std::wstring> itemContainer;

	// assume scanner just got the KL_CT_ITEM_ADD
	bool command_add_item(KLScanner* scanner, std::vector<std::wstring>& container)
	{
		bool result = true;

		KLToken token;
		int r = scanner->ScanToken(&token);
		if (r == 0 || token.tokenType != KL_TOKEN_LEFT_PAREN)
		{
			result = false;
			goto END;
		}

		int addCount = 0;
		while ( r != 0 )
		{
			// Get an item
			++addCount;

			int index = 0;
			wchar_t ch = 0;
			while ((ch = scanner->Next()) && (ch != _T(',') && ch != _T(')')))
			{
				token.string[index++] = ch;
			}
			token.string[index] = _T('\0');
			container.push_back(token.string);

			scanner->PutBack(ch);
			r = scanner->ScanToken(&token);
			if (token.tokenType == KL_TOKEN_COMMA)
				continue;
			else if (token.tokenType == KL_TOKEN_RIGHT_PAREN)
				break;
			else
			{
				result = false;
				goto END;
			}
		}
		
		if (r == 0 || token.tokenType != KL_TOKEN_RIGHT_PAREN)
		{
			result = false;
		}

	END:
		// 넣었던 거 취소하기
		if (result == false)
		{
			while (addCount--) container.pop_back();
		}

		return result;
	}

	struct KLCommand
	{
		KLCommandType type;
		std::vector<std::wstring> object;
	};

	std::vector<KLCommand> commandBuffer;
	void executeCommandBuffer(const std::vector<KLCommand>& buffer);

	static bool isKLRun = true;
	void enterInternal()
	{
		KLScanner* scanner = new KLScanner();
		KLToken token;
		int r = 0;
		auto scanAndPrintErr = [&r, scanner, &token]
		{
			r = scanner->ScanToken(&token);
			if (r == 0)
				std::wcout << "ERROR : " << token.string << _T('\n');
		};
		auto printTokenErrMsg = [](KLTokenErrorType err)
		{
			std::wcout << TokenErrorMessages[(int)err] << _T('\n');
		};
		auto isNonParamFunc = [&scanAndPrintErr, &printTokenErrMsg](const KLToken& token, bool& isError, KLTokenErrorType err) -> bool
		{
			scanAndPrintErr();
			if (token.tokenType != KL_TOKEN_LEFT_PAREN) 
				printTokenErrMsg(err), isError = true;

			if (isError) return !isError;

			scanAndPrintErr();
			if (token.tokenType != KL_TOKEN_RIGHT_PAREN) 
				printTokenErrMsg(err), isError = true;

			return !isError;
		};

		do
		{
			commandBuffer.clear();

			std::wcout << _T(':'); // Prompt
			scanAndPrintErr();
			if (token.tokenType != KL_TOKEN_COMMAND_BEGIN)
			{
				printTokenErrMsg(KL_ERR_UNVALID_COMMAND_START);
				continue;
			}

			// After Command Begin
			bool isError = false;
			while ((r = scanner->ScanToken(&token)) && token.tokenType != KL_TOKEN_COMMAND_END)
			{
				isError = false;

				switch (token.commandType)
				{
				case KL_CT_ITEM_ADD:
				{
					if (false == command_add_item(scanner, itemContainer))
					{
						isError = true;
						printTokenErrMsg(KL_ERR_UNVALID_COMMAND_ITEM_ADD);
					}
					break;
				}
				case KL_CT_ITEM_CLEAR:
				{
					if (true == isNonParamFunc(token, isError, KL_ERR_UNVALID_COMMAND_ITEM_CLEAR))
					{
						itemContainer.clear();
					}

					break;
				}
				case KL_CT_ITEM_PRINT:
				{
					if (true == isNonParamFunc(token, isError, KL_ERR_UNVALID_COMMAND_ITEM_PRINT))
					{
						commandBuffer.push_back({ KL_CT_ITEM_PRINT, itemContainer });
					}

					break;
				}
				case KL_CT_EXIT:
				{
					if (true == isNonParamFunc(token, isError, KL_ERR_UNVALID_COMMAND_EXIT))
					{
						commandBuffer.push_back({ KL_CT_EXIT, });
					}

					break;
				}
				default:
					isError = true;
					printTokenErrMsg(KL_ERR_UNVALID_COMMAND);
					break;
				}

				if (isError) break;
			}

			if (isError)
			{
				scanner->PutBack(&token);
				scanner->CleanUpInput();
				continue;
			}

			if (r == 0)
			{
				std::wcout << "ERROR : " << token.string << _T('\n');
				continue;
			}

			if (token.tokenType != KL_TOKEN_COMMAND_END)
			{
				printTokenErrMsg(KL_ERR_UNVALID_COMMAND_END);
				continue;
			}
			
			// After Command End, execute Commands
			executeCommandBuffer(commandBuffer);

		} while (isKLRun);

		delete scanner;

		KLDLG->EndDialog(IDCANCEL);
	}

	void executeCommandBuffer(const std::vector<KLCommand>& buffer)
	{

		for (size_t i = 0; i < buffer.size(); ++i)
		{
#if 0
			std::wcout << _T("Command : ") << ReverseCommandMap[buffer[i].type] << _T('\n');
#endif

			if (!isKLRun) break;

			switch (buffer[i].type)
			{
			case KL_CT_EXIT:
			{
				isKLRun = false;
				break;
			}
			case KL_CT_ITEM_PRINT:
			{
				for (size_t j = 0; j < buffer[i].object.size(); ++j)
					std::wcout << buffer[i].object[j] << _T('\n');
				break;
			}
			
			}
		}


	}
}

