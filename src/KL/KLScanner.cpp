#include "KL/KLScanner.hpp"
#include <iostream>
#include <tchar.h>

#include "stdafx.h"

namespace KiwoomLogger
{
	KLScanner::KLScanner() 
	{
		InitCommandMap();
	}

	static bool isAlpha(wchar_t ch)
	{
		if ((ch >= _T('a') && ch <= _T('z')) || (ch >= _T('A') && ch <= _T('Z')))
		{
			return true;
		}

		return false;
	}

	static bool isDigit(wchar_t ch)
	{
		if (ch >= _T('0') && ch <= _T('9'))
		{
			return true;
		}

		return false;
	}

	static bool isWhiteSpace(wchar_t c)
	{
		if (_T(' ') == c || _T('\t') == c || _T('\n') == c || _T('\r') == c || _T('\f') == c)
		{
			return true;
		}

		return false;
	}

	static void copy_token_error_message(KLTokenErrorType errType, wchar_t* dest)
	{
		wcscpy_s(dest, TokenStringSize, TokenErrorMessages[(int)errType]);
	}

	// when you read unwanted character,
	// you will put the character into this
	wchar_t putBackCh;
	void KLScanner::PutBack(wchar_t c)
	{
		putBackCh = c;
	}

	// Get the next character from user Input
	wchar_t KLScanner::Next()
	{
		wchar_t c;

		if (putBackCh)
		{
			c = putBackCh;
			putBackCh = 0;
			return c;
		}

		std::wcin.get(c);

		return c;
	}

	// Skip past input that we don't need to deal with
	// i.e., whitespace, newlines. Return the first
	// character we need to deal with.
	wchar_t KLScanner::Skip()
	{
		wchar_t c;

		c = Next();
		while (isWhiteSpace(c))
		{
			c = Next();
		}
		return (c);
	}

	wchar_t scannerBuffer[512] = { 0, };
	static void putCharAddIndex(int& index, wchar_t ch) { scannerBuffer[index++] = ch; }

	int KLScanner::ScanToken(KLToken* tok)
	{
		wchar_t ch = Skip();

		switch (ch)
		{
		case _T(','):
			tok->tokenType = KL_TOKEN_COMMA;
			wcscpy_s(tok->string, TokenStringSize, _T(","));
			break;
		case _T(':'):
			copy_token_error_message(KL_ERR_UNVALID_TOKEN, tok->string);
			CleanUpInput();
			return 0;
		case _T(';'):
			tok->tokenType = KL_TOKEN_SEMICOLON;
			wcscpy_s(tok->string, TokenStringSize, _T(";"));
			break;
		case _T('('):
			tok->tokenType = KL_TOKEN_LEFT_PAREN;
			wcscpy_s(tok->string, TokenStringSize, _T("("));
			break;
		case _T(')'):
			tok->tokenType = KL_TOKEN_RIGHT_PAREN;
			wcscpy_s(tok->string, TokenStringSize, _T(")"));
			break;
		default:
			if (isAlpha(ch) || ch == _T('_'))
			{
				int sbufIndex = 0;
				putCharAddIndex(sbufIndex, ch);

				while (std::wcin.get(ch) && (isAlpha(ch) || isDigit(ch) || ch == _T('_')))
					putCharAddIndex(sbufIndex, ch);
				std::wcin.putback(ch);

				scannerBuffer[sbufIndex] = _T('\0');

				// KL Command Begin
				if (CommandMap.count(scannerBuffer) > 0)
				{
					tok->tokenType = KL_TOKEN_COMMAND;
					tok->commandType = CommandMap[scannerBuffer];
					wcscpy_s(tok->string, TokenStringSize, scannerBuffer);
					break;
				}
			}

			copy_token_error_message(KL_ERR_UNVALID_TOKEN, tok->string);
			CleanUpInput();
			return 0;
		}


		return 1;
	}

	void KLScanner::CleanUpInput()
	{
		// clear all until the place where a user enter new line
		putBackCh = 0;

		wchar_t ch;
		while (std::wcin.get(ch))
		{
			if (ch == _T(';'))
				return;
		}
	}
}