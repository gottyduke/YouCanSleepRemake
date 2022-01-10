#include "Config.h"


namespace Config
{
	Boolean EnableSleepWait[8]{
		{"InAir"},
		{"Trespassing"},
		{"AskedToLeave"},
		{"GuardsPursuing"},
		{"EnemiesNearby"},
		{"TakingHealthDamage"},
		{"Owned"},
		{"InUse"},
	};


	void Load()
	{
		auto main = COMPILE_PROXY("YouCanSleepRemake.toml"sv);

		for (auto index = 0; index < std::extent_v<decltype(EnableSleepWait)>; ++index) {
			main.Bind(EnableSleepWait[index], true);
		}

		main.Load();

		INFO("Config Loaded"sv);
	}
}