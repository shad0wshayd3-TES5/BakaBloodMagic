#pragma once

namespace BloodMagic
{
	class Forms
	{
	public:
		inline static RE::BGSKeyword* BloodMagic_DisableEffectScaling{ nullptr };
		inline static RE::BGSKeyword* BloodMagic_RequiresBloodMagicActive{ nullptr };

		static void Register()
		{
			if (auto TESDataHandler = RE::TESDataHandler::GetSingleton())
			{
				if (TESDataHandler->GetLoadedModIndex(PLUGIN_NAME))
				{
					BloodMagic_DisableEffectScaling =
						TESDataHandler->LookupForm<RE::BGSKeyword>(0x2862, PLUGIN_NAME);

					BloodMagic_RequiresBloodMagicActive =
						TESDataHandler->LookupForm<RE::BGSKeyword>(0x2865, PLUGIN_NAME);
				}
			}
		}

	private:
		inline static constexpr char PLUGIN_NAME[] = "BloodMagic.esp";
	};
}
