#pragma once
#ifndef __KL_PARSER_HPP__
#define __KL_PARSER_HPP__

#include "KL/KLTokenType.hpp"

namespace KiwoomLogger
{
	class KLScanner;

	struct KLASTnode
	{
		KLCommandType type;
		KLASTnode* next;
	};



	class KLParser
	{
	public:
		KLParser() = delete;
		KLParser(KLScanner* scanner);

		KLASTnode* Parse(wchar_t* errBuffer, int bufferSize);
	private:
		KLScanner* m_scanner;
	};
}

#endif