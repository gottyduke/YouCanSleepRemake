#include "Settings.h"


bool Settings::LoadSettings(const bool a_dumpParse)
{
	auto [log, success] = J2S::load_settings(FILE_NAME, a_dumpParse);

	if (!log.empty()) {
		_ERROR("%s", log.c_str());
	}

	allows[0] = &allowSleepAndWaitInAir;
	allows[1] = &allowSleepAndWaitTrespassing;
	allows[2] = &allowSleepAndWaitAskedToLeave;
	allows[3] = &allowSleepAndWaitGuardsPursuing;
	allows[4] = &allowSleepAndWaitEnemiesNearby;
	allows[5] = &allowSleepAndWaitTakingHealthDamage;
	allows[6] = &allowSleepAndWaitInUse;
	allows[7] = &allowSleepAndWaitOwned;
	
	return success;
}


decltype(Settings::allowSleepAndWaitInAir) Settings::allowSleepAndWaitInAir("allowSleepAndWaitInAir", true);
decltype(Settings::allowSleepAndWaitTrespassing) Settings::allowSleepAndWaitTrespassing("allowSleepAndWaitTrespassing", true);
decltype(Settings::allowSleepAndWaitAskedToLeave) Settings::allowSleepAndWaitAskedToLeave("allowSleepAndWaitAskedToLeave", true);
decltype(Settings::allowSleepAndWaitGuardsPursuing) Settings::allowSleepAndWaitGuardsPursuing("allowSleepAndWaitGuardsPursuing", true);
decltype(Settings::allowSleepAndWaitEnemiesNearby) Settings::allowSleepAndWaitEnemiesNearby("allowSleepAndWaitEnemiesNearby", true);
decltype(Settings::allowSleepAndWaitTakingHealthDamage) Settings::allowSleepAndWaitTakingHealthDamage("allowSleepAndWaitTakingHealthDamage", true);
decltype(Settings::allowSleepAndWaitInUse) Settings::allowSleepAndWaitInUse("allowSleepAndWaitInUse", true);
decltype(Settings::allowSleepAndWaitOwned) Settings::allowSleepAndWaitOwned("allowSleepAndWaitOwned", true);
decltype(Settings::allows) Settings::allows {};
