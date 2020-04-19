#include "KL/KLScanner.hpp"
#include <iostream>
#include <tchar.h>

#include "stdafx.h"

namespace KiwoomLogger
{
	KLScanner::KLScanner() {}

	static void copy_token_error_message(KLTokenErrorType errType, wchar_t* dest)
	{
		wcscpy_s(dest, TokenStringSize, TokenErrorMessages[(int)errType]);
	}

	// when you read unwanted character,
	// you will put the character into this
	wchar_t PutBack;
	static void putback(wchar_t c)
	{
		PutBack = c;
	}

	static void clean_up_input()
	{
		// clear all until the place where a user enter new line
		PutBack = 0;

		wchar_t ch;
		while (std::wcin.get(ch))
		{
			if (ch == _T('\n'))
				return;
		}
	}

	// Get the next character from user Input
	static wchar_t next()
	{
		wchar_t c;

		if (PutBack)
		{
			c = PutBack;
			PutBack = 0;
			return c;
		}

		std::wcin.get(c);

		return c;
	}

	// Skip past input that we don't need to deal with
	// i.e., whitespace, newlines. Return the first
	// character we need to deal with.
	static wchar_t skip()
	{
		wchar_t c;

		c = next();
		while (_T(' ') == c || _T('\t') == c || _T('\n') == c || _T('\r') == c || _T('\f') == c)
		{
			c = next();
		}
		return (c);
	}

	int KLScanner::ScanToken(KLToken* tok)
	{
		if (skip() != _T('K') || skip() != _T('L'))
		{
			copy_token_error_message(NOT_KL_SPECIFIED, tok->string);
			clean_up_input();
			return 0;
		}

		wchar_t ch = skip();

		if(ch == _T'-')

		return 1;
	}
}