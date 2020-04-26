#include "KL/KLParser.hpp"
#include "KL/KLScanner.hpp"

using namespace KiwoomLogger;

KLParser::KLParser(KLScanner* scanner)
	: m_scanner(scanner)
{}

KLASTnode* KLParser::Parse(wchar_t* errBuffer, int bufferSize)
{
	return nullptr;
}