#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace roblox {
	class instance
	{
	public:
		uintptr_t address;
		uintptr_t primitive();
		
		std::string name();
		std::string classname();


		roblox::instance findfirstchild(std::string n);
		roblox::instance findclass(std::string n);

		roblox::instance localplayer();
		roblox::instance model_instance();


		std::vector< roblox::instance > children();
	};

}