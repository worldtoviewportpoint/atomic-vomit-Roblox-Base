#include "m.hpp"
#include "../gamehacks/driver.h"
#include "../cache/cache.h"

auto m::hook_modules() -> void {
	mem::process_id = mem::find_process("RobloxPlayerBeta.exe");
	mem::find_driver();

	c_sys::init_cache_system();
}