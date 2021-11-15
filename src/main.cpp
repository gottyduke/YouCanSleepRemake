#include "Hooks.h"
#include "Config.h"


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface * a_skse, SKSE::PluginInfo * a_info)
{
	DKUtil::Logger::Init(Version::PROJECT, Version::NAME);

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	if (a_skse->IsEditor()) {
		ERROR("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		ERROR("Unsupported runtime version {}", ver.string());
		return false;
	}

	return true;
}


extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface * a_skse)
{
	INFO("{} v{} loaded", Version::PROJECT, Version::NAME);

	SKSE::Init(a_skse);

	Config::Load();

	Hooks::Install();

	return true;
}
