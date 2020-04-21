#pragma once
#ifndef __KL_SCANNER_HPP__
#define __KL_SCANNER_HPP__

#include "KLTokenType.hpp"

namespace KiwoomLogger
{
	class KLScanner
	{
	public:
		KLScanner();
		
		// return 1 when token is valid
		// return 0 when token is invalid
		// string member of Token will be filled 
		// with the error, when token is invalid
		int ScanToken(KLToken* tok);
		void PutBack(KLToken* tok);
		void CleanUpInput();

		// per-character functions
		wchar_t Next();
		wchar_t Skip();
		void PutBack(wchar_t c);
	private:

	};
}


#endif