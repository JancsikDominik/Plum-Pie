#ifndef PLUM_ASSERT_HPP
#define PLUM_ASSERT_HPP

#include <iostream>

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
		bool errorOccured = false;
		GLenum err = glGetError();
		while (err != GL_NO_ERROR)
	    {
			switch(err)
			{
			case GL_INVALID_ENUM:
				std::cerr << "[OpenGL ERROR]: invalid enum, " << stmt << std::endl;
				break;
			case GL_INVALID_VALUE:
				std::cerr << "[OpenGL ERROR]: invalid value, " << stmt << std::endl;
				break;
			case GL_INVALID_OPERATION:
				std::cerr << "[OpenGL ERROR]: invalid operation, " << stmt << std::endl;
				break;
			case GL_STACK_OVERFLOW:
				std::cerr << "[OpenGL ERROR]: stack overflow, " << stmt << std::endl;
				break;
			case GL_OUT_OF_MEMORY:
				std::cerr << "[OpenGL ERROR]: out of memory, " << stmt << std::endl;
				break;
			default:
				std::cerr << "[OpenGL ERROR] : unknown error, " << stmt << std::endl;
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
            if(Plum::Debug::Opengl::CheckOpenGLError(#stmt)) __debugbreak(); \
        } while (0)
#else
	#define GL_CALL(stmt) stmt
#endif



#endif
