#include "KL/KLTokenType.hpp"

namespace KiwoomLogger
{
	static bool isCommandMapInit = false;
	std::unordered_map<std::wstring, KLCommandType> CommandMap;
	std::unordered_map<KLCommandType, std::wstring> ReverseCommandMap;
	void InitCommandMap()
	{
		if (isCommandMapInit) return;

		isCommandMapInit = true;
		
		size_t identifierNum = sizeof(CommandStr) / sizeof(wchar_t*);
		for (size_t i = 0; i < identifierNum; ++i)
		{
			CommandMap[CommandStr[i]] = (KLCommandType)i;
			ReverseCommandMap[(KLCommandType)i] = CommandStr[i];
		}
	}
}