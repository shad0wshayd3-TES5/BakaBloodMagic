#pragma once

#include "BloodMagic/Settings.h"

namespace BloodMagic
{
	class Papyrus
	{
	public:
		static bool Register(RE::BSScript::IVirtualMachine* a_vm)
		{
			a_vm->RegisterFunction("GetVersion", CLASS_NAME, GetVersion, true);
			a_vm->RegisterFunction("GraveRobberHeal", CLASS_NAME, GraveRobberHeal);
			a_vm->RegisterFunction("UpdateSettings", CLASS_NAME, UpdateSettings);
			logger::info(FMT_STRING("Registered funcs for class {:s}"), CLASS_NAME);

			return true;
		}

	private:
		inline static constexpr char CLASS_NAME[] = "BloodMagicNative";

		enum
		{
			kVersion = 1
		};

		static std::int32_t GetVersion(RE::StaticFunctionTag*)
		{
			return kVersion;
		}

		static void GraveRobberHeal(RE::StaticFunctionTag*, RE::Actor* a_actor)
		{
			auto fHealthVal = a_actor->GetActorValue(RE::ActorValue::kHealth);
			auto fHealthMax = a_actor->GetBaseActorValue(RE::ActorValue::kHealth) +
			                  a_actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kPermanent, RE::ActorValue::kHealth) +
			                  a_actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kHealth);

			auto fHealthPct = fHealthVal / fHealthMax;
			for (auto& [iThreshold, iHealthMod] : Settings::GraveRobber::HealthMap)
			{
				auto fThreshold = iThreshold / 100.0f;
				auto fHealthMod = iHealthMod / 100.0f;
				if (fHealthPct <= fThreshold)
				{
					a_actor->RestoreActorValue(
						RE::ACTOR_VALUE_MODIFIER::kDamage,
						RE::ActorValue::kHealth,
						fHealthMax * fHealthMod);
					break;
				}
			}
		}

		static void UpdateSettings(RE::StaticFunctionTag*)
		{
			Settings::Update();
		}
	};
}
