#pragma once

#include "BloodMagic/Settings.h"

namespace BloodMagic
{
	class Actor
	{
	private:
		static bool UpdateRegenDelay(RE::Actor* a_this, RE::ActorValue a_actorValue, float a_secondsElapsed)
		{
			if (Utils::IsBloodMagicActive(a_this))
			{
				switch (a_actorValue)
				{
				case RE::ActorValue::kHealth:
				case RE::ActorValue::kMagicka:
					return true;
				default:
					break;
				}
			}

			auto RegenDelay = a_this->GetRegenDelay(a_actorValue);
			if (RegenDelay <= 0.0f)
			{
				return false;
			}

			RegenDelay = std::max(RegenDelay - a_secondsElapsed, 0.0f);
			a_this->UpdateRegenDelay(a_actorValue, RegenDelay);

			return RegenDelay > 0.0f;
		}

	public:
		static void InstallHooks()
		{
			static REL::Relocation target{ RELOCATION_ID(37516, 38461) };
			target.replace_func(OFFSET(0x94, 0x90), UpdateRegenDelay);
		}
	};
}
