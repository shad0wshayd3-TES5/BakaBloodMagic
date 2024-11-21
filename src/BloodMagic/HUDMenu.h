#pragma once

namespace BloodMagic
{
	class HUDMenu
	{
	private:
		static RE::UI_MESSAGE_RESULTS ProcessMessage(RE::HUDMenu* a_this, RE::UIMessage& a_message)
		{
			if (a_this)
			{
				RE::GFxValue Health;
				if (a_this->root.GetMember("Health", &Health))
				{
					if (!Health.HasMember("HealthFlashInstance"))
					{
						RE::GFxValue Depth, HealthFlashInstance;
						Health.Invoke("getNextHighestDepth", &Depth);
						Health.CreateEmptyMovieClip(
							&HealthFlashInstance,
							"HealthFlashInstance",
							static_cast<std::uint32_t>(Depth.GetSInt()));

						std::array<RE::GFxValue, 1> args{ "BloodMagic/WarningFlash.swf" };
						HealthFlashInstance.Invoke("loadMovie", args);
					}
				}
			}

			return _ProcessMessage(a_this, a_message);
		}

		inline static REL::Relocation<decltype(&RE::HUDMenu::ProcessMessage)> _ProcessMessage;

	public:
		static void InstallHooks()
		{
			REL::Relocation<std::uintptr_t> vtbl{ RE::HUDMenu::VTABLE[0] };
			_ProcessMessage = vtbl.write_vfunc(0x04, ProcessMessage);
		}
	};
}
