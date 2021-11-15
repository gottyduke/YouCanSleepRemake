#include "Hooks.h"
#include "Config.h"


namespace Hooks
{
	constexpr auto SW_FUNC_ID = 39371;
	constexpr std::uint8_t JMP = 0xEB;
	constexpr std::uint8_t NOP = 0x90;
	constexpr std::uintptr_t OffsetTbl[8] = {
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
	constexpr std::uint8_t InAirHookNop[6]{ NOP, NOP, NOP, NOP, NOP, NOP };


	void Install()
	{
		const auto funcAddr = REL::ID(SW_FUNC_ID).address();
		const auto anniFuncAddr = funcAddr + 0x27E70;

		for (auto i = 0; i < 8; ++i) {
			if (*Config::EnableSleepWait[i]) {
				WRITE(funcAddr + OffsetTbl[i], JMP);
			}
		}

		// loop check for in air position
		if (*Config::EnableSleepWait[0]) {
			WRITE_BUF(funcAddr + InAirLoopOffset, InAirHookNop, 6);
		}

		INFO("Hooks installed"sv);
	}
}
