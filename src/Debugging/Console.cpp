#include <Windows.h>
#include <consoleapi2.h>

#include "Console.hpp"
#include "Debug.hpp"

namespace Plum::Debug
{
	Console::Console()
	{
	#ifdef PLUM_DEBUG
		Init();
	#endif
	}

	Console::~Console()
	{
	#ifdef PLUM_DEBUG
		Release();
	#endif
	}


	void Console::Init()
	{
		// WINDOWS ONLY!
		AllocConsole();

		// opening stdin, stdout and std err console channels
		auto inResult = freopen_s(&m_inStream, "CONIN$", "rb", stdin);
		auto outResult = freopen_s(&m_outStream, "CONOUT$", "wb", stdout);
		auto errResult = freopen_s(&m_errStream, "CONOUT$", "wb", stderr);
		assert(inResult == 0);
		assert(outResult == 0);
		assert(errResult == 0);

		SetConsoleTitle("Plum debug console");
		
		// WINDOWS ONLY!
		m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void Console::Release()
	{
		// closing opened channels
		fclose(m_inStream);
		fclose(m_outStream);
		fclose(m_errStream);

		FreeConsole();
		m_consoleHandle = nullptr;
	}

	void Console::SetConsoleColor(ConsoleColor color)
	{
	#ifdef PLUM_DEBUG
		switch (color)
		{
		case ConsoleColor::Green:
			// WINDOWS ONLY!
			SetConsoleTextAttribute(m_consoleHandle, 2);
			break;
		case ConsoleColor::Red:
			SetConsoleTextAttribute(m_consoleHandle, 4);
			break;
		case ConsoleColor::Yellow:
			SetConsoleTextAttribute(m_consoleHandle, 6);
			break;
		case ConsoleColor::White:
			SetConsoleTextAttribute(m_consoleHandle, 7);
			break;
		default:
			PLUM_ASSERT(false);
		}
	#endif
	}
}