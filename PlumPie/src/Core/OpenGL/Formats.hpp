#pragma once

namespace Plum::GL
{
	enum class GLTypes : int
	{
		Unknown = -1,
		Byte = 0x1400,
		UByte = 0x1401,
		Short = 0x1402,
		UShort = 0x1403,
		Int = 0x1404,
		UInt = 0x1405,
		Float = 0x1406,
		TwoBytes = 0x1407,
		ThreeBytes = 0x1408,
		FourBytes = 0x1409,
		Double = 0x140A
	};
}