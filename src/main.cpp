#include "Hooks.h"
#include "Settings.h"
#include "version.h"

#include "SKSE/API.h"


extern "C"
{
	bool SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\YouCanSleepRemake.log");
		SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::UseLogStamp(true);

		_MESSAGE("YouCanSleepRemake v%s", YCSR_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "YouCanSleepRemake";
		a_info->version = YCSR_VERSION_MAJOR;

		if (a_skse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!\n");
			return false;
		}

		const auto ver = a_skse->RuntimeVersion();
		if (ver <= SKSE::RUNTIME_1_5_39) {
			_FATALERROR("Unsupported runtime version %s!", ver.GetString().c_str());
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("YouCanSleepRemake loaded");

		if (!Init(a_skse)) {
			return false;
		}

		if (Settings::LoadSettings()) {
			_MESSAGE("Settings loaded successfully");
		} else {
			_FATALERROR("Failed to retrieve settings!");
			return false;
		}

		if (Hooks::TryInstallHooks()) {
			_MESSAGE("Successfully installed hooks");
			_MESSAGE("You Can Sleep Now. Or Can You?");
		} else {
			_FATALERROR("Failed to install hooks!");
			return false;
		}
		
		return true;
	}
};
