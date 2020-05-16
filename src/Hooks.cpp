#include "Hooks.h"
#include "Settings.h"

#include "SKSE/SafeWrite.h"


namespace
{
	constexpr auto FUNC_ID = 39371;
	constexpr std::uint8_t JMP = 0xEB;
	constexpr std::uintptr_t AddressTable[8] = {
		0x2E, // You cannot sleep in the air.
		0x89, // You cannot sleep while trespassing.
		0xB1, // You cannot sleep while being asked to leave.
		0xF6, // You cannot sleep while guards are pursuing you.
		0x11F, // You cannot sleep when enemies are nearby.
		0x146, // You cannot sleep while taking health damage.
		0x1BB, // This object is already in use by someone else.
		0x3BC // You cannot sleep in an owned bed.
	};
	constexpr std::uintptr_t InAirLoopOffset = 0xD4;
	constexpr std::uint8_t InAirHookNop[6] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
}


namespace Hooks
{

	bool TryInstallHooks()
	{
		auto success = true;

		const auto funcAddr = REL::ID(FUNC_ID).GetAddress();
		
		for (auto i = 0; i < 8; ++i) {
			if (**Settings::allows[i]) {
				success &=
					SKSE::SafeWrite8(funcAddr + AddressTable[i], JMP);
			}
		}

		// loop check for in air position
		if (*Settings::allowSleepAndWaitInAir) {
			SKSE::SafeWriteBuf(funcAddr + InAirLoopOffset, InAirHookNop, 6);
		}
		
		return success;
	}
}
