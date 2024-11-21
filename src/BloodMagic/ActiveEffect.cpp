#include "BloodMagic/ActiveEffect.h"

namespace BloodMagic
{
	template<>
	void ActiveEffect::Hook<RE::AbsorbEffect>::AdjustForPerks(
		RE::AbsorbEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::AccumulatingValueModifierEffect>::AdjustForPerks(
		RE::AccumulatingValueModifierEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ActiveEffect>::AdjustForPerks(
		RE::ActiveEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::BanishEffect>::AdjustForPerks(
		RE::BanishEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::BoundItemEffect>::AdjustForPerks(
		RE::BoundItemEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::CalmEffect>::AdjustForPerks(
		RE::CalmEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::CloakEffect>::AdjustForPerks(
		RE::CloakEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::CommandEffect>::AdjustForPerks(
		RE::CommandEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::CommandSummonedEffect>::AdjustForPerks(
		RE::CommandSummonedEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ConcussionEffect>::AdjustForPerks(
		RE::ConcussionEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::CureEffect>::AdjustForPerks(
		RE::CureEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::DarknessEffect>::AdjustForPerks(
		RE::DarknessEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::DemoralizeEffect>::AdjustForPerks(
		RE::DemoralizeEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::DetectLifeEffect>::AdjustForPerks(
		RE::DetectLifeEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::DisarmEffect>::AdjustForPerks(
		RE::DisarmEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::DisguiseEffect>::AdjustForPerks(
		RE::DisguiseEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::DispelEffect>::AdjustForPerks(
		RE::DispelEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::DualValueModifierEffect>::AdjustForPerks(
		RE::DualValueModifierEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		NegateHealthRestore(
			a_this,
			a_target->GetTargetAsActor(),
			a_this->actorValue,
			&a_this->magnitude);

		NegateHealthRestore(
			a_this,
			a_target->GetTargetAsActor(),
			a_this->secondaryActorValue,
			&a_this->secondaryAVWeight);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::EnhanceWeaponEffect>::AdjustForPerks(
		RE::EnhanceWeaponEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::EtherealizationEffect>::AdjustForPerks(
		RE::EtherealizationEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::FrenzyEffect>::AdjustForPerks(
		RE::FrenzyEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::GrabActorEffect>::AdjustForPerks(
		RE::GrabActorEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::GuideEffect>::AdjustForPerks(
		RE::GuideEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::InvisibilityEffect>::AdjustForPerks(
		RE::InvisibilityEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::LightEffect>::AdjustForPerks(
		RE::LightEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::LockEffect>::AdjustForPerks(
		RE::LockEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::NightEyeEffect>::AdjustForPerks(
		RE::NightEyeEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::OpenEffect>::AdjustForPerks(
		RE::OpenEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ParalysisEffect>::AdjustForPerks(
		RE::ParalysisEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::PeakValueModifierEffect>::AdjustForPerks(
		RE::PeakValueModifierEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		NegateHealthRestore(
			a_this,
			a_target->GetTargetAsActor(),
			a_this->actorValue,
			&a_this->magnitude);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::RallyEffect>::AdjustForPerks(
		RE::RallyEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ReanimateEffect>::AdjustForPerks(
		RE::ReanimateEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ScriptEffect>::AdjustForPerks(
		RE::ScriptEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ScriptedRefEffect>::AdjustForPerks(
		RE::ScriptedRefEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::SlowTimeEffect>::AdjustForPerks(
		RE::SlowTimeEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::SoulTrapEffect>::AdjustForPerks(
		RE::SoulTrapEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::SpawnHazardEffect>::AdjustForPerks(
		RE::SpawnHazardEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::StaggerEffect>::AdjustForPerks(
		RE::StaggerEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::SummonCreatureEffect>::AdjustForPerks(
		RE::SummonCreatureEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::TelekinesisEffect>::AdjustForPerks(
		RE::TelekinesisEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::TurnUndeadEffect>::AdjustForPerks(
		RE::TurnUndeadEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ValueAndConditionsEffect>::AdjustForPerks(
		RE::ValueAndConditionsEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		NegateHealthRestore(
			a_this,
			a_target->GetTargetAsActor(),
			a_this->actorValue,
			&a_this->magnitude);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::ValueModifierEffect>::AdjustForPerks(
		RE::ValueModifierEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		NegateHealthRestore(
			a_this,
			a_target->GetTargetAsActor(),
			a_this->actorValue,
			&a_this->magnitude);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::VampireLordEffect>::AdjustForPerks(
		RE::VampireLordEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::WerewolfEffect>::AdjustForPerks(
		RE::WerewolfEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}

	template<>
	void ActiveEffect::Hook<RE::WerewolfFeedEffect>::AdjustForPerks(
		RE::WerewolfFeedEffect* a_this,
		RE::Actor* a_caster,
		RE::MagicTarget* a_target)
	{
		ApplyBloodMagic(a_this, a_caster);
		return _AdjustForPerks(a_this, a_caster, a_target);
	}
}
