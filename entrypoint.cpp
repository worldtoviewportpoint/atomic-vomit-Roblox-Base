#include "mapper/mapper.h"
#include <Windows.h>
#include "modules/m.hpp"

auto main() -> void
{
	auto console = GetConsoleWindow();
	ShowWindow(console, SW_HIDE);

	auto console_name = "";
	SetConsoleTitle(console_name);

	auto map = true;
	if (map) load_driver();

	auto hook = true;
	if (hook) m::hook_modules();

	system("pause");
}