#pragma once
#include <vector>
#include "../roblox/instance.h"


namespace i_sys {

	roblox::instance game;

	roblox::instance visualengine;

	roblox::instance players;

	roblox::instance localplayer;

	roblox::instance workspace;

	roblox::instance camera;

	roblox::instance hood_custom_aim;

	roblox::instance da_hood_aim;


}
namespace e_sys {

	std::vector< entity > entities;

}