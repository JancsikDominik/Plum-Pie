#pragma once

namespace Plum::Mouse
{

	enum class EventType
	{
		Move,
		// ModeChange, <- will implement at some point, just lazy af and not that useful
		ButtonPress,
		Scroll
	};

	enum class ButtonAction : int32_t
	{
		Invalid = -1,
		Release	= 0,
		Press	= 1
	};

	enum class Button : int32_t
	{
		Unknown = -1,
		Left    = 0,
		Right   = 1,
		Middle  = 2,
		Mouse4  = 3,
		Mouse5  = 4,
		Mouse6  = 5,
		Mouse7  = 6,
		Mouse8  = 7
	};

}