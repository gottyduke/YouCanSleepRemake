#pragma once

#include "Json2Settings.h"


namespace J2S = Json2Settings;

class Settings
{
public:
	Settings() = delete;

	static bool LoadSettings(bool a_dumpParse = false);

	
	static J2S::bSetting allowSleepAndWaitInAir;
	static J2S::bSetting allowSleepAndWaitTrespassing;
	static J2S::bSetting allowSleepAndWaitAskedToLeave;
	static J2S::bSetting allowSleepAndWaitGuardsPursuing;
	static J2S::bSetting allowSleepAndWaitEnemiesNearby;
	static J2S::bSetting allowSleepAndWaitTakingHealthDamage;
	static J2S::bSetting allowSleepAndWaitInUse;
	static J2S::bSetting allowSleepAndWaitOwned;


	static J2S::bSetting* allows[8];
private:
	static constexpr auto FILE_NAME = R"(Data\SKSE\Plugins\YouCanSleepRemake.json)";
};
