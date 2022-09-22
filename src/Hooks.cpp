#include "Hooks.h"
#include "Config.h"


namespace Hooks
{
	constexpr OpCode JmpShort = 0xEB;
	constexpr OpCode NOP = DKUtil::Hook::detail::NOP;

	constexpr std::uint64_t AE_FuncID = 40443;
	constexpr std::uint64_t SE_FuncID = 39371;

	constexpr std::ptrdiff_t InAirLoopOffset = 0xD4;
	
	constexpr std::uint8_t InAirHookNop[6]{ NOP, NOP, NOP, NOP, NOP, NOP };


	void Install()
	{
		std::ptrdiff_t OffsetTbl[8] = {
			0x2E,                        // You cannot sleep in the air.
			0x89,                        // You cannot sleep while trespassing.
			0xB1,                        // You cannot sleep while being asked to leave.
			0xF6,                        // You cannot sleep while guards are pursuing you.
			0x11F,                       // You cannot sleep when enemies are nearby.
			0x146,                       // You cannot sleep while taking health damage.
			0x1BB,                       // This object is already in use by someone else.
			REL::Relocate(0x3BC, 0x3C0)  // You cannot sleep in an owned bed.
		};

		const auto funcAddr = DKUtil::Hook::IDToAbs(AE_FuncID, SE_FuncID);

		for (auto index = 0; index < std::extent_v<decltype(Config::EnableSleepWait)>; ++index) {
			if (*Config::EnableSleepWait[index]) {
				DKUtil::Hook::WriteImm(funcAddr + OffsetTbl[index], JmpShort);
				INFO("Enabled SleepWait {} at 0x{:X}", Config::EnableSleepWait[index].get_key(), OffsetTbl[index]);
			}
		}

		// loop check for in air position
		if (*Config::EnableSleepWait[0]) {
			DKUtil::Hook::WriteData(funcAddr + InAirLoopOffset, &InAirHookNop, sizeof(InAirHookNop));
		}

		INFO("Hooks installed"sv);
	}
}
