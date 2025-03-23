#include "cache.h"
#include "../gamehacks/driver.h"
#include "../gamehacks/offsets.h"
#include "../storage/storage.h"
#include <thread>

auto c_sys::cache_addresses ( ) -> void {
	cache::base = mem::find_image();
	cache::datamodel = read<uintptr_t>(cache::base + offsets::FakeDataModelPointer + offsets::FakeDataModelToDataModel);
	cache::visualengine = read<uintptr_t>(cache::base + offsets::VisualEnginePointer);
}

auto c_sys::cache_entities ( ) -> void {
    while (true) {
        if (GetAsyncKeyState(VK_END)) {
            exit(0);
        }

        std::vector<entity> tempPlayerstructs;
        if (i_sys::players.address != 0) {
            tempPlayerstructs.reserve(100);
            for (auto player : i_sys::players.children()) {
                if (player.address == i_sys::localplayer.address) continue;

                auto character = player.model_instance();
                auto hrp = character.findfirstchild("HumanoidRootPart");
                auto head = character.findfirstchild("Head");

                entity plrstruct;
                plrstruct.name = player.name();
                plrstruct.head = head;
          
                tempPlayerstructs.push_back(plrstruct);
            }

            e_sys::entities = tempPlayerstructs;
        }
    }
}


auto c_sys::init_cache_system ( ) -> void {
	c_sys::cache_addresses();
	auto datamodel = static_cast<roblox::instance>(cache::datamodel);
	auto visualengine = static_cast<roblox::instance>(cache::visualengine);
	auto players = datamodel.findfirstchild("Players");
	auto localplayer = players.localplayer();
	auto workspace = datamodel.findfirstchild("Workspace");
	auto camera = workspace.findfirstchild("Camera");
	auto hood_customs_aim = localplayer.findfirstchild("PlayerGui").findfirstchild("Main Screen")
		.findfirstchild("Aim");
	auto da_hood_aim = localplayer.findfirstchild("PlayerGui").findfirstchild("MainScreenGui")
		.findfirstchild("Aim");
	i_sys::game = datamodel;
	i_sys::visualengine = visualengine;
	i_sys::players = players;
	i_sys::localplayer = localplayer;
	i_sys::workspace = workspace;
	i_sys::camera = camera;
	i_sys::hood_custom_aim = hood_customs_aim;
	i_sys::da_hood_aim = da_hood_aim;
    std::thread(cache_entities).detach();

}