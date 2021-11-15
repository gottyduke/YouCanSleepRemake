#include "Config.h"


namespace Config
{
	Boolean EnableSleepWait[8]{
		{"EnableSleepAndWaitInAir"},
		{"EnableSleepAndWaitTrespassing"},
		{"EnableSleepAndWaitAskedToLeave"},
		{"EnableSleepAndWaitGuardsPursuing"},
		{"EnableSleepAndWaitEnemiesNearby"},
		{"EnableSleepAndWaitTakingHealthDamage"},
		{"EnableSleepAndWaitOwned"},
		{"EnableSleepAndWaitInUse"},
	};


	void Load()
	{
		auto main = COMPILE_PROXY("YouCanSleepRemake.toml"sv);

		for (auto& config : EnableSleepWait) {
			main.Bind(config, true);
		}

		main.Load();

		INFO("Config Loaded"sv);
	}
}