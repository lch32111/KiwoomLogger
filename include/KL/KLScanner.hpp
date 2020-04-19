#pragma once
#ifndef __KL_SCANNER_HPP__
#define __KL_SCANNER_HPP__

namespace KiwoomLogger
{
	enum KLTokenType
	{
		KL_TOKEN_PRINT_HELP,
		KL_TOKEN_EOF,
	};

	enum KLTokenErrorType
	{
		NOT_KL_SPECIFIED
	};

	static const wchar_t* TokenErrorMessages[] =
	{
		L"명령 앞에 KL를 명시하세요",
	};

	static const size_t TokenStringSize = 512;
	struct KLToken
	{
		KLTokenType type;
		wchar_t string[TokenStringSize] = { 0, };
	};

	class KLScanner
	{
	public:
		KLScanner();
		
		// return 1 when token is valid
		// return 0 when token is invalid
		// string member of Token will be filled 
		// with the error, when token is invalid
		int ScanToken(KLToken* tok);
	private:

	};
}


#endif