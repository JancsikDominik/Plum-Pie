#include <Windows.h>
#include <consoleapi2.h>

#include "Console.hpp"

namespace Plum::Debug
{
	void Console::Init()
	{
		AllocConsole();

		// opening stdin, stdout and std err console channels
		auto inResult = freopen_s(&m_inStream, "CONIN$", "rb", stdin);
		auto outResult = freopen_s(&m_outStream, "CONOUT$", "wb", stdout);
		auto errResult = freopen_s(&m_errStream, "CONOUT$", "wb", stderr);
		assert(inResult == 0);
		assert(outResult == 0);
		assert(errResult == 0);

		SetConsoleTitle(L"Plum debug console");
	}

	void Console::Release()
	{
		// closing opened channels
		fclose(m_inStream);
		fclose(m_outStream);
		fclose(m_errStream);

		FreeConsole();
	}
}