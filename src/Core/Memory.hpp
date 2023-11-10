#ifndef PLUMPIE_MEMORY_HPP
#define PLUMPIE_MEMORY_HPP

#include <memory>

namespace Plum
{
	// alias for unique_ptr
	template <class T, class Deleter = std::default_delete<T>>
	using Owned = std::unique_ptr<T, Deleter>;

	// alias for shared_ptr
	template <class T>
	using Ref = std::shared_ptr<T>;
}

namespace Plum::Ptr
{
	// Alias for std::make_unique
	template <typename T, typename... Args>
	auto MakeOwned(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// Alias for std::make_unique
	template <typename T, typename... Args>
	auto MakeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#endif