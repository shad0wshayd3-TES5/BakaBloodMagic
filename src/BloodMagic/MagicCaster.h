#pragma once

#include "BloodMagic/Utils.h"

namespace BloodMagic
{
	/*
	class MagicCaster
	{
	private:
		static bool ReleaseCast(RE::MagicCaster* a_this, RE::TESBoundObject* a_source, bool a_playReleaseSound)
		{
			if (!a_this->currentSpell)
			{
				a_this->FinishCast();
				return false;
			}

			// for (auto Sound : a_this->sounds)
			// {
			// 	Sound.Stop();
			// }

			auto bIsCasting = a_this->state.get() == RE::MagicCaster::State::kCasting;
			a_this->state = RE::MagicCaster::State::kCharging;

			auto Reason{ RE::MagicSystem::CannotCastReason::kOK };
			auto EffectivenessMult{ 1.0f };

			auto bCastingOk =
				a_this->CheckCast(
					a_this->currentSpell,
					a_this->GetIsDualCasting(),
					&EffectivenessMult,
					&Reason,
					false) ||
				(bIsCasting && Reason == RE::MagicSystem::CannotCastReason::kShoutWhileRecovering);

			std::uint32_t TargetCount{ 0 };
			if (bCastingOk && a_this->FindTargets(EffectivenessMult, TargetCount, a_source, false, false))
			{
				if (!bIsCasting)
				{
					a_this->SpellCast(true, TargetCount, a_this->currentSpell);
					a_this->nextTargetUpdate = a_this->castingTimer + RE::MagicSystem::GetMagicCasterTargetUpdateInterval();

					if (a_playReleaseSound)
					{
						a_this->PlayReleaseSound(a_this->currentSpell);
					}
				}

				return true;
			}
			else
			{
				if (auto Actor = a_this->GetCasterAsActor())
				{
					auto SpellType = a_this->currentSpell->GetSpellType();
					auto bIsNotWortCraft = SpellType != RE::MagicSystem::SpellType::kWortCraft;

					if (a_this->currentSpell->GetAVEffect())
					{
						if (bIsNotWortCraft)
						{
							if (auto FailureSound = RE::MagicSystem::GetMagicFailureSound(SpellType))
							{
								RE::BSSoundHandle Result;
								Actor->PlayASound(Result, FailureSound->formID, false, 0x11);
							}
						}
					}

					if (Actor == RE::PlayerCharacter::GetSingleton())
					{
						if (bIsNotWortCraft || a_this->currentSpell->IsFood())
						{
							Utils::ShowCannotCastReason(Reason);
						}
					}
				}

				a_this->InterruptCast(true);
				return false;
			}
		}

	public:
		static void InstallHooks()
		{
			REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(33629, 34407) };
			stl::asm_replace(target.address(), OFFSET(0x20E, 0x250), reinterpret_cast<std::uintptr_t>(ReleaseCast));
		}
	};
	*/
}
