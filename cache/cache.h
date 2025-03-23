#pragma once
#include <cstdint>
#include "../roblox/instance.h"
#include "../roblox/math.h"

namespace cache {
	inline uintptr_t base;
	inline uintptr_t datamodel;
	inline uintptr_t visualengine;
}
struct bones
{
	roblox::instance* bone;
	Vector3 size;
};
struct entity {
	roblox::instance head;
	roblox::instance humanoidrootpart;
	std::string userid;
	std::string name;
};


namespace c_sys {
	auto cache_addresses ( ) -> void;
	auto cache_entities ( ) -> void;
	auto cache_bones ( ) -> void;
	auto init_cache_system ( ) -> void;
}