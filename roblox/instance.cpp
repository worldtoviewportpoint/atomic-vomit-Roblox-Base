#include "instance.h"
#include "../gamehacks/fetchstring.h"
#include "../gamehacks/offsets.h"

std::string roblox::instance::name()
{
	return fetchstring(read<uintptr_t>(this -> address + offsets::Name));
}

std::string roblox::instance::classname()
{
	return fetchstring(read<uintptr_t>(this -> address + offsets::ClassDescriptor));
}

uintptr_t roblox::instance::primitive() {
	return read<uintptr_t>(this -> address + offsets::Primitive);
}

std::vector< roblox::instance > roblox::instance::children() {
	std::vector < roblox::instance > returned;
	auto child_begin = read<uintptr_t>(this->address + offsets::Children);
	auto child_end = read<uintptr_t>(child_begin + offsets::ChildrenEnd);

	for (auto instances = read<std::uint64_t>(child_begin); instances != child_end; instances += 16u)
	{
		returned.emplace_back(read<roblox::instance>(instances));
	}

	return returned;

}

roblox::instance roblox::instance::findfirstchild(std::string n) {
	auto children = this -> children();
	for (auto instance : children) {
		if (instance.name() == n) return instance;
	}
}
roblox::instance roblox::instance::findclass(std::string n) {
	auto children = this->children();
	for (auto instance : children) {
		if (instance.classname() == n) return instance;
	}
}

roblox::instance roblox::instance::localplayer() {
	return read<roblox::instance>(this -> address + offsets::LocalPlayer);
}
roblox::instance roblox::instance::model_instance() {
	return read<roblox::instance>(this->address + offsets::ModelInstance);
}