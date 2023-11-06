#ifndef PLUM_ASSERT_HPP
#define PLUM_ASSERT_HPP

#include <iostream>
#include <GLFW/glfw3.h>
#include "Console.hpp"


///========================================================================================
///																						  |
/// EVERYTING IN THIS HEADER FILE IS DEBUG ONLY (THESE WON'T DO ANYTHING IN RELEASE MODE) |
///																					      |
///========================================================================================

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#define STR(x) #x


// Custom assert macro
#ifndef PLUM_DEBUG
	#define PLUM_ASSERT(x) ;
#else
	#define PLUM_ASSERT(expr) if (!(expr))																														\
							   {																																    \
								   printf("Assertion failed (%s): \nfunction %s \nfile %s \nline %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__);			\
								   __debugbreak();																													\
							   }
#endif


namespace Plum::Debug::Opengl
{
	inline static void ClearGLErrors()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	inline static bool CheckOpenGLError(const char* stmt)
	{
		// kinda a junkie fix, but couldn't think about a better way
		// if there is no opengl context this function gets into an infinite loop
		if (glfwGetCurrentContext() == nullptr)
		{
			Console::LogGLError("no opengl context");
			return false;
		}

		bool errorOccured = false;
		GLenum err = glGetError();
		while (err != GL_NO_ERROR)
	    {
			switch(err)
			{
			case GL_INVALID_ENUM:
				Console::LogGLError("invalid enum, %s", stmt);
				break;
			case GL_INVALID_VALUE:
				Console::LogGLError("invalid value, %s", stmt);
				break;
			case GL_INVALID_OPERATION:
				Console::LogGLError("invalid operation, %s", stmt);
				break;
			case GL_STACK_OVERFLOW:
				Console::LogGLError("stack overflow, %s", stmt);
				break;
			case GL_OUT_OF_MEMORY:
				Console::LogGLError("out of memory, %s", stmt);
				break;
			default:
				Console::LogGLError("unknown error, %s", stmt);
				break;
			}
			err = glGetError();
			errorOccured = true;
	    }
		return errorOccured;
	}
}

// used for getting opengl error pop-ups in debug mode
#ifdef PLUM_DEBUG
	#define GL_CALL(stmt) do {																	 \
            stmt;																				 \
            if(Plum::Debug::Opengl::CheckOpenGLError(#stmt)) __debugbreak();					 \
        } while (0)
#else
	#define GL_CALL(stmt) stmt
#endif



#endif
