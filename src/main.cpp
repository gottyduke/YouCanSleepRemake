#include "Config.h"
#include "Hooks.h"


DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	DKUtil::Logger::Init(Plugin::NAME, REL::Module::get().version().string());

	SKSE::Init(a_skse);

	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);

	// do stuff
	Config::Load();

	Hooks::Install();
	
	return true;
}