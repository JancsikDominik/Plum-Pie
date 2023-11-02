#pragma once
#include <cassert>
#include <string>

namespace Plum::Debug
{
	/**
	 * \brief RAII wrapper around a windows console
	 */
	class Console final
	{
	public:
		enum class ConsoleColor
		{
			White,
			Red,
			Yellow,
			Green
		};


		// Constructors/Destructors
		Console();
		~Console();


		/**
		 * \brief wrapper around printf function, that only prints if we are in debug mode
		 */
		template <typename ... Args>
		static void Log(char const* const format, Args const& ... args)
		{
		#ifdef PLUM_DEBUG
			// have to initialize console before using it
			assert(m_inStream != nullptr && m_outStream != nullptr && m_errStream != nullptr);
			printf((format + std::string("\n")).c_str(), args ...);
		#endif
		}

		template <typename ... Args>
		static void LogInfo(char const* const format, Args const& ... args)
		{
			SetConsoleColor(ConsoleColor::Yellow);
			Log((std::string("[INFO] ") + format).c_str(), args ...);
			SetConsoleColor(ConsoleColor::White);
		}

		template <typename ... Args>
		static void LogError(char const* const format, Args const& ... args)
		{
			SetConsoleColor(ConsoleColor::Red);
			Log((std::string("[ERROR] ") + format).c_str(), args ...);
			SetConsoleColor(ConsoleColor::White);
		}

		template <typename ... Args>
		static void LogGLError(char const* const format, Args const& ... args)
		{
			SetConsoleColor(ConsoleColor::Red);
			Log((std::string("[OpenGL ERROR] ") + format).c_str(), args ...);
			SetConsoleColor(ConsoleColor::White);
		}

		static void SetConsoleColor(ConsoleColor color);

	private:
		static void Init();
		static void Release();

		inline static FILE* m_inStream = nullptr;
		inline static FILE* m_outStream = nullptr;
		inline static FILE* m_errStream = nullptr;

		inline static void* m_consoleHandle = nullptr;
	};
}
