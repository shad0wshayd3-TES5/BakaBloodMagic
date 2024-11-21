#pragma once

#include "BloodMagic/Settings.h"

namespace BloodMagic
{
	class Utils
	{
	private:
		static bool FlashTrueHUDMeter(RE::Actor* a_actor, RE::ActorValue a_actorValue, bool a_long);

	public:
		static void DamageActorValue(RE::Actor* a_actor, RE::ActorValue a_actorValue, float a_value)
		{
			switch (a_actorValue)
			{
			case RE::ActorValue::kMagicka:
			{
				if (Utils::IsBloodMagicActive(a_actor))
				{
					return a_actor->RestoreActorValue(
						RE::ACTOR_VALUE_MODIFIER::kDamage,
						RE::ActorValue::kHealth,
						a_value * (1.0f / Settings::Modifiers::fBloodMagicCostScale));
				}

				break;
			}

			default:
				break;
			}

			return a_actor->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, a_actorValue, a_value);
		}

		static void FlashHealthMeter(RE::Actor* a_actor)
		{
			if (FlashTrueHUDMeter(a_actor, RE::ActorValue::kHealth, true))
			{
				return;
			}

			auto UI = RE::UI::GetSingleton();
			if (!UI)
			{
				return;
			}

			auto HUDMenu = UI->GetMenu<RE::HUDMenu>();
			if (!HUDMenu)
			{
				return;
			}

			RE::GFxValue Health, HealthFlash;
			if (!HUDMenu->root.GetMember("Health", &Health))
			{
				return;
			}

			if (Health.GetMember("HealthFlashInstance", &HealthFlash))
			{
				std::array<RE::GFxValue, 1> args;
				Health.GetMember("_currentFrame", args.data());
				Health.Invoke("PlayForward", args);
				HealthFlash.GotoAndPlay("StartFlash");
			}
		}

		static float GetActorValue(RE::Actor* a_actor, RE::ActorValue a_actorValue)
		{
			switch (a_actorValue)
			{
			case RE::ActorValue::kMagicka:
			{
				if (Utils::IsBloodMagicActive(a_actor))
				{
					return (a_actor->GetActorValue(RE::ActorValue::kHealth) * Settings::Modifiers::fBloodMagicCostScale);
				}

				break;
			}

			default:
				break;
			}

			return a_actor->GetActorValue(a_actorValue);
		}

		static float GetBaseActorValue(RE::Actor* a_actor, RE::ActorValue a_actorValue)
		{
			switch (a_actorValue)
			{
			case RE::ActorValue::kMagicka:
			{
				if (Utils::IsBloodMagicActive(a_actor))
				{
					return (a_actor->GetBaseActorValue(RE::ActorValue::kHealth) * Settings::Modifiers::fBloodMagicCostScale);
				}

				break;
			}

			default:
				break;
			}

			return a_actor->GetBaseActorValue(a_actorValue);
		}

		static float GetMagickaCost(RE::MagicItem* a_magicItem, RE::Actor* a_actor, bool a_dualCast)
		{
			auto MagickaCost = a_magicItem->CalculateMagickaCost(a_actor);
			if (a_dualCast)
			{
				MagickaCost = RE::MagicFormulas::CalcDualCastCost(MagickaCost);
			}

			return MagickaCost;
		}

		static std::int32_t GetStepCount()
		{
			auto PlayerCharacter = RE::PlayerCharacter::GetSingleton();
			if (!PlayerCharacter)
			{
				return 0;
			}

			auto HealthDamage = PlayerCharacter->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kHealth);
			if (HealthDamage >= 0.0)
			{
				return 0;
			}

			HealthDamage = abs(HealthDamage);
			return static_cast<std::int32_t>(floor(HealthDamage / Settings::Modifiers::fBloodMagicStepRate));
		}

		static void InterruptActor(RE::Actor* a_actor, RE::MagicSystem::CastingSource a_castingSource)
		{
			switch (a_castingSource)
			{
			case RE::MagicSystem::CastingSource::kLeftHand:
				RE::SourceActionMap::DoAction(a_actor, RE::DEFAULT_OBJECT::kActionLeftInterrupt);
				break;
			case RE::MagicSystem::CastingSource::kRightHand:
				RE::SourceActionMap::DoAction(a_actor, RE::DEFAULT_OBJECT::kActionRightInterrupt);
				break;
			case RE::MagicSystem::CastingSource::kOther:
				RE::SourceActionMap::DoAction(a_actor, RE::DEFAULT_OBJECT::kActionVoiceInterrupt);
				break;
			default:
				break;
			}
		}

		static bool IsBloodMagicActive(RE::Actor* a_actor)
		{
			return Settings::General::bBloodMagicActive &&
			       a_actor == RE::PlayerCharacter::GetSingleton();
		}

		template <typename T>
		inline static void SafeSet(T* a_ptr, T a_value)
		{
			if (a_ptr)
			{
				*a_ptr = a_value;
			}
		}

		static void ShowCannotCastReason(RE::MagicSystem::CannotCastReason a_reason)
		{
			switch (a_reason)
			{
			case RE::MagicSystem::CannotCastReason::kMagicka:
			{
				if (Settings::General::bBloodMagicActive)
				{
					return RE::DebugNotification("You don't have enough Health", nullptr, true);
				}

				break;
			}

			default:
				break;
			}

			auto CannotCastString = RE::MagicSystem::GetCannotCastString(a_reason);
			if (!CannotCastString)
			{
				return;
			}

			RE::DebugNotification(CannotCastString, nullptr, true);
		}
	};
}
