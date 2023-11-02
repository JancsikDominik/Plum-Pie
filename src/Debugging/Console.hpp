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
		Console()
		{
		#ifdef PLUM_DEBUG
			Init();
		#endif
		}
		~Console()
		{
		#ifdef PLUM_DEBUG
			Release();
		#endif
		}


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
			Log((std::string("[INFO] ") + format).c_str(), args ...);
		}

		template <typename ... Args>
		static void LogError(char const* const format, Args const& ... args)
		{
			Log((std::string("[ERROR] ") + format).c_str(), args ...);
		}

		template <typename ... Args>
		static void LogGLError(char const* const format, Args const& ... args)
		{
			Log((std::string("[OpenGL ERROR] ") + format).c_str(), args ...);
		}

	private:
		static void Init();
		static void Release();

		inline static FILE* m_inStream = nullptr;
		inline static FILE* m_outStream = nullptr;
		inline static FILE* m_errStream = nullptr;
	};
}
