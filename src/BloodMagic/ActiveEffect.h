#pragma once

#include "BloodMagic/Forms.h"
#include "BloodMagic/Settings.h"
#include "BloodMagic/Utils.h"

namespace BloodMagic
{
	class ActiveEffect
	{
	private:
		template <class Effect>
		class Hook
		{
		private:
			static void AdjustForPerks(
				Effect* a_this,
				RE::Actor* a_caster,
				RE::MagicTarget* a_target);

			inline static REL::Relocation<decltype(&Effect::AdjustForPerks)> _AdjustForPerks;

		public:
			static void Install()
			{
				REL::Relocation<std::uintptr_t> vtbl{ Effect::VTABLE[0] };
				_AdjustForPerks = vtbl.write_vfunc(0x00, AdjustForPerks);
			}
		};

		inline static void ApplyBloodMagic(RE::ActiveEffect* a_this, RE::Actor* a_caster)
		{
			if (!Utils::IsBloodMagicActive(a_caster))
			{
				return;
			}

			switch (a_this->spell->GetSpellType())
			{
			case RE::MagicSystem::SpellType::kDisease:
			case RE::MagicSystem::SpellType::kPower:
			case RE::MagicSystem::SpellType::kLesserPower:
			case RE::MagicSystem::SpellType::kAbility:
			case RE::MagicSystem::SpellType::kPoison:
			case RE::MagicSystem::SpellType::kEnchantment:
			case RE::MagicSystem::SpellType::kPotion:
			case RE::MagicSystem::SpellType::kWortCraft:
			case RE::MagicSystem::SpellType::kAddiction:
			case RE::MagicSystem::SpellType::kVoicePower:
			case RE::MagicSystem::SpellType::kStaffEnchantment:
			case RE::MagicSystem::SpellType::kScroll:
				return;

			default:
				break;
			}

			if (a_this->effect && a_this->effect->baseEffect)
			{
				if (a_this->effect->baseEffect->HasKeyword(
						BloodMagic::Forms::BloodMagic_DisableEffectScaling))
				{
					return;
				}
			}

			a_this->duration *= Settings::Modifiers::fBloodMagicDurationScale;
			a_this->magnitude *= Settings::Modifiers::fBloodMagicMagnitudeScale;

			auto StepCount = Utils::GetStepCount();
			if (StepCount >= 1)
			{
				a_this->duration *= (1.0f + (Settings::Modifiers::fBloodMagicStepDurationScale * StepCount));
				a_this->magnitude *= (1.0f + (Settings::Modifiers::fBloodMagicStepMagnitudeScale * StepCount));
			}
		}

		inline static void NegateHealthRestore(RE::ActiveEffect* a_this, RE::Actor* a_target, RE::ActorValue a_actorValue, float* a_value)
		{
			if (!Utils::IsBloodMagicActive(a_target))
			{
				return;
			}

			if (a_this->IsCausingHealthDamage())
			{
				return;
			}

			if (a_actorValue != RE::ActorValue::kHealth)
			{
				return;
			}

			Utils::SafeSet(a_value, 0.0f);
		}

	public:
		static void InstallHooks()
		{
			Hook<RE::AbsorbEffect>::Install();
			Hook<RE::AccumulatingValueModifierEffect>::Install();
			Hook<RE::ActiveEffect>::Install();
			Hook<RE::BanishEffect>::Install();
			Hook<RE::BoundItemEffect>::Install();
			Hook<RE::CalmEffect>::Install();
			Hook<RE::CloakEffect>::Install();
			Hook<RE::CommandEffect>::Install();
			Hook<RE::CommandSummonedEffect>::Install();
			Hook<RE::ConcussionEffect>::Install();
			Hook<RE::CureEffect>::Install();
			Hook<RE::DarknessEffect>::Install();
			Hook<RE::DemoralizeEffect>::Install();
			Hook<RE::DetectLifeEffect>::Install();
			Hook<RE::DisarmEffect>::Install();
			Hook<RE::DisguiseEffect>::Install();
			Hook<RE::DispelEffect>::Install();
			Hook<RE::DualValueModifierEffect>::Install();
			Hook<RE::EnhanceWeaponEffect>::Install();
			Hook<RE::EtherealizationEffect>::Install();
			Hook<RE::FrenzyEffect>::Install();
			Hook<RE::GrabActorEffect>::Install();
			Hook<RE::GuideEffect>::Install();
			Hook<RE::InvisibilityEffect>::Install();
			Hook<RE::LightEffect>::Install();
			Hook<RE::LockEffect>::Install();
			Hook<RE::NightEyeEffect>::Install();
			Hook<RE::OpenEffect>::Install();
			Hook<RE::ParalysisEffect>::Install();
			Hook<RE::PeakValueModifierEffect>::Install();
			Hook<RE::RallyEffect>::Install();
			Hook<RE::ReanimateEffect>::Install();
			Hook<RE::ScriptEffect>::Install();
			Hook<RE::ScriptedRefEffect>::Install();
			Hook<RE::SlowTimeEffect>::Install();
			Hook<RE::SoulTrapEffect>::Install();
			Hook<RE::SpawnHazardEffect>::Install();
			Hook<RE::StaggerEffect>::Install();
			Hook<RE::SummonCreatureEffect>::Install();
			Hook<RE::TelekinesisEffect>::Install();
			Hook<RE::TurnUndeadEffect>::Install();
			Hook<RE::ValueAndConditionsEffect>::Install();
			Hook<RE::ValueModifierEffect>::Install();
			Hook<RE::VampireLordEffect>::Install();
			Hook<RE::WerewolfEffect>::Install();
			Hook<RE::WerewolfFeedEffect>::Install();
		}
	};
}
