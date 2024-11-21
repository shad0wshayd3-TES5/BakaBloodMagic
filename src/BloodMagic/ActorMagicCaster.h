#pragma once

#include "BloodMagic/Settings.h"
#include "BloodMagic/Utils.h"

namespace BloodMagic
{
	class ActorMagicCaster
	{
	private:
		static void InterruptCastHelper(RE::ActorMagicCaster* a_this, RE::MagicSystem::CannotCastReason a_reason)
		{
			if (a_this->currentSpell &&
			    a_this->actor == RE::PlayerCharacter::GetSingleton())
			{
				RE::PlayerCharacter::GetSingleton()->PlayMagicFailureSound(a_this->currentSpell->GetSpellType());
				switch (a_reason)
				{
					case RE::MagicSystem::CannotCastReason::kMagicka:
						{
							if (Settings::General::bBloodMagicActive)
							{
								Utils::FlashHealthMeter(a_this->actor);
								break;
							}

							RE::HUDMenu::FlashMeter(RE::ActorValue::kMagicka);
							break;
						}

					case RE::MagicSystem::CannotCastReason::kShoutWhileRecovering:
						{
							RE::HUDMenu::FlashMeter(RE::ActorValue::kVoiceRate);
							break;
						}

					default:
						break;
				}

				Utils::ShowCannotCastReason(a_reason);
				if (a_reason == RE::MagicSystem::CannotCastReason::kItemCharge &&
				    a_this->currentSpell->GetSpellType() == RE::MagicSystem::SpellType::kStaffEnchantment)
				{
					RE::TutorialMenu::OpenTutorialMenu(RE::DEFAULT_OBJECT::kHelpWeaponCharge);
				}
			}

			if (a_this->actor)
			{
				Utils::InterruptActor(a_this->actor, a_this->castingSource);
			}

			a_this->SetCurrentSpell(nullptr);
			a_this->flags.reset(
				RE::ActorMagicCaster::Flags::kNone,
				RE::ActorMagicCaster::Flags::kDualCasting);
		}

		static void InterruptCastImpl(RE::ActorMagicCaster* a_this, bool a_refund)
		{
			if (a_refund &&
			    RE::MagicUtilities::UsesResourceWhileCharging(a_this->currentSpell, a_this->castingSource) &&
			    a_this->costCharged > 0.0f)
			{
				if (a_this->state.get() <= RE::MagicCaster::State::kUnk04 ||
				    a_this->state.get() == RE::MagicCaster::State::kCasting)
				{
					auto ResourceAcV = RE::MagicUtilities::GetAssociatedResource(a_this->currentSpell, a_this->castingSource);
					if (ResourceAcV != RE::ActorValue::kNone)
					{
						Utils::DamageActorValue(a_this->actor, ResourceAcV, a_this->costCharged);
					}
				}
			}

			if (a_this->flags.none(RE::ActorMagicCaster::Flags::kCheckDeferredInterrupt) ||
			    a_this->flags.all(RE::ActorMagicCaster::Flags::kDeferInterrupt))
			{
				Utils::InterruptActor(a_this->actor, a_this->castingSource);
			}
			else
			{
				a_this->flags.reset(
					RE::ActorMagicCaster::Flags::kCheckDeferredInterrupt,
					RE::ActorMagicCaster::Flags::kDeferInterrupt);
				a_this->flags.set(RE::ActorMagicCaster::Flags::kDeferInterrupt);
			}

			if (a_this->interruptHandler)
			{
				a_this->interruptHandler(a_this->actor);
			}

			a_this->flags.reset(
				RE::ActorMagicCaster::Flags::kNone,
				RE::ActorMagicCaster::Flags::kDualCasting);
		}

		static void SpellCast(RE::ActorMagicCaster* a_this, bool a_success, std::uint32_t a_targetCount, RE::SpellItem* a_spell)
		{
			if (!a_success)
			{
				return;
			}

			if (!a_spell)
			{
				if (!a_this->currentSpell)
				{
					return;
				}

				a_spell = a_this->currentSpell->As<RE::SpellItem>();
				if (!a_spell)
				{
					return;
				}
			}

			switch (a_spell->GetSpellType())
			{
				case RE::MagicSystem::SpellType::kSpell:
				case RE::MagicSystem::SpellType::kDisease:
				case RE::MagicSystem::SpellType::kPower:
				case RE::MagicSystem::SpellType::kLesserPower:
					{
						a_this->actor->AddCastPower(a_spell);
						break;
					}

				case RE::MagicSystem::SpellType::kVoicePower:
					{
						if (!a_this->actor->IsCurrentShout(a_spell))
						{
							break;
						}

						if (auto CurrentShout = a_this->actor->GetCurrentShout())
						{
							for (auto i = 0; i < 3; i++)
							{
								auto Variation = CurrentShout->variations[i];
								if (Variation.spell)
								{
									a_this->actor->AddCastPower(Variation.spell);
									continue;
								}

								break;
							}
						}

						break;
					}

				case RE::MagicSystem::SpellType::kScroll:
					{
						a_this->actor->RemoveCastScroll(a_spell, a_this->castingSource);
						break;
					}

				default:
					break;
			}

			if (!a_spell->IsFood() &&
			    (a_spell->GetSpellType() != RE::MagicSystem::SpellType::kEnchantment || a_spell->GetDelivery() != RE::MagicSystem::Delivery::kTouch || a_targetCount) &&
			    RE::MagicUtilities::UsesResourceOnRelease(a_spell, a_this->castingSource))
			{
				auto MagickaCost = Utils::GetMagickaCost(a_spell, a_this->actor, a_this->GetIsDualCasting());
				auto ResourceAcV = RE::MagicUtilities::GetAssociatedResource(a_spell, a_this->castingSource);
				if (ResourceAcV != RE::ActorValue::kNone && MagickaCost > 0.0f)
				{
					Utils::DamageActorValue(a_this->actor, ResourceAcV, -MagickaCost);
				}
			}

			if (a_spell->HasEffect(RE::EffectArchetype::kInvisibility))
			{
				a_this->actor->DispelAlteredStates(RE::EffectArchetype::kInvisibility);
			}

			if (a_spell->HasEffect(RE::EffectArchetype::kEtherealize))
			{
				a_this->actor->DispelAlteredStates(RE::EffectArchetype::kEtherealize);
			}

			if (a_this->actor == RE::PlayerCharacter::GetSingleton())
			{
				if (auto EffectSetting = a_spell->GetAVEffect())
				{
					if (auto ImageSpaceMod = EffectSetting->data.imageSpaceMod)
					{
						ImageSpaceMod->TriggerIfNotActive(1.0, nullptr);
					}
				}
			}

			if (auto ScriptEventSourceHolder = RE::ScriptEventSourceHolder::GetSingleton())
			{
				if (auto RefHandle = a_this->actor->CreateRefHandle())
				{
					ScriptEventSourceHolder->SendSpellCastEvent(RefHandle.get(), a_spell->formID);
				}
			}
		}

		static bool CheckCast(RE::ActorMagicCaster* a_this, RE::MagicItem* a_spell, bool a_dualCast, float* a_alchStrength, RE::MagicSystem::CannotCastReason* a_reason, bool a_useBaseValueForCost)
		{
			Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kOK);
			if (a_this->flags.any(RE::ActorMagicCaster::Flags::kSkipCheckCast))
			{
				return true;
			}

			if (!a_spell)
			{
				if (!a_this->currentSpell)
				{
					return false;
				}

				a_spell = a_this->currentSpell;
				a_dualCast = a_this->GetIsDualCasting();
			}

			auto bIsPlayer = a_this->actor == RE::PlayerCharacter::GetSingleton();
			auto bIsPlayerAndGodMode = bIsPlayer && RE::PlayerCharacter::IsGodMode();

			if (bIsPlayerAndGodMode &&
			    a_spell->GetSpellType() != RE::MagicSystem::SpellType::kWortCraft)
			{
				return true;
			}

			auto bHasResource{ true };
			auto bBlockMulticasting{ false };
			auto bBlockShoutRecovery{ false };
			auto bBlockWhileSCasting{ false };
			auto bBlockWhileShouting{ false };

			if (!bIsPlayerAndGodMode)
			{
				if (a_this->actor->GetVoiceRecoveryTime() > 0.0f &&
				    a_spell->GetSpellType() == RE::MagicSystem::SpellType::kVoicePower)
				{
					bBlockShoutRecovery = true;
				}

				auto MagickaCost = 0.0f;
				auto ResourceAcV = RE::MagicUtilities::GetAssociatedResource(a_spell, a_this->castingSource);
				if (ResourceAcV != RE::ActorValue::kNone)
				{
					MagickaCost = Utils::GetMagickaCost(a_spell, a_this->actor, a_dualCast);
				}

				auto bUsesResource{ false };
				switch (a_this->state.get())
				{
					case RE::MagicCaster::State::kNone:
					case RE::MagicCaster::State::kUnk01:
						{
							bUsesResource = ResourceAcV != RE::ActorValue::kNone;
							break;
						}

					case RE::MagicCaster::State::kUnk04:
						{
							bUsesResource = RE::MagicUtilities::UsesResourceWhileCasting(a_spell, a_this->castingSource);
							break;
						}

					case RE::MagicCaster::State::kCharging:
						{
							bUsesResource = RE::MagicUtilities::UsesResourceOnRelease(a_spell, a_this->castingSource);
							break;
						}

					default:
						break;
				}

				if (bUsesResource &&
				    MagickaCost > 0.0f)
				{
					auto Magicka = (a_useBaseValueForCost)
					                   ? Utils::GetBaseActorValue(a_this->actor, ResourceAcV)
					                   : Utils::GetActorValue(a_this->actor, ResourceAcV);

					bHasResource = (a_spell->GetCastingType() == RE::MagicSystem::CastingType::kConcentration)
					                   ? Magicka > 0.0f
					                   : bHasResource = Magicka >= MagickaCost;
				}
			}

			if (a_spell->GetSpellType() != RE::MagicSystem::SpellType::kEnchantment &&
			    a_spell->GetCastingType() != RE::MagicSystem::CastingType::kConstantEffect)
			{
				auto Reason{ RE::MagicSystem::CannotCastReason::kOK };
				for (std::uint32_t i = 0; i < a_spell->effects.size(); i++)
				{
					if (auto effect = a_spell->effects[i])
					{
						if (bIsPlayer
						        ? !RE::PlayerCharacter::GetSingleton()->CheckCast(a_spell, effect, Reason)
						        : !RE::ActiveEffectFactory::CheckCast(a_this, a_spell, effect, Reason))
						{
							Utils::SafeSet(a_reason, Reason);
							return false;
						}

						if (auto BaseEffect = effect->baseEffect)
						{
							auto ActiveCasters = a_this->actor->WhoIsCasting();
							if (BaseEffect->data.delivery == RE::MagicSystem::Delivery::kSelf &&
							    BaseEffect->data.archetype == RE::EffectSetting::Archetype::kAccumulateMagnitude)
							{
								bBlockMulticasting = (ActiveCasters & ~(1 << std::to_underlying(a_this->castingSource))) != 0;
							}

							bBlockWhileShouting = (ActiveCasters & 4) != 0 &&
							                      a_this->castingSource <= RE::MagicSystem::CastingSource::kRightHand;
							bBlockWhileSCasting = (ActiveCasters & 3) != 0 &&
							                      a_this->castingSource == RE::MagicSystem::CastingSource::kOther;

							if (bBlockMulticasting || bBlockWhileSCasting || bBlockWhileShouting)
							{
								break;
							}
						}
					}
				}
			}

			if (bBlockShoutRecovery)
			{
				Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kShoutWhileRecovering);
			}
			else if (bHasResource)
			{
				if (bBlockMulticasting)
				{
					Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kMultipleCast);
				}
				else if (bBlockWhileShouting)
				{
					Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kCastWhileShouting);
				}
				else if (bBlockWhileSCasting)
				{
					Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kShoutWhileCasting);
				}
			}
			else
			{
				Utils::SafeSet(a_reason, RE::MagicUtilities::GetAssociatedResourceReason(a_spell, a_this->castingSource));
			}

			switch (a_spell->GetSpellType())
			{
				case RE::MagicSystem::SpellType::kSpell:
				case RE::MagicSystem::SpellType::kPoison:
				case RE::MagicSystem::SpellType::kStaffEnchantment:
					{
						if (a_spell->HasKeyword(BloodMagic::Forms::BloodMagic_RequiresBloodMagicActive))
						{
							if (!Utils::IsBloodMagicActive(a_this->actor))
							{
								Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kOK);
								return false;
							}
						}

						if (bHasResource && !bBlockWhileShouting)
						{
							return true;
						}

						return false;
					}

				case RE::MagicSystem::SpellType::kPower:
					{
						if (a_this->actor->IsInCastPowerList(a_spell->As<RE::SpellItem>()))
						{
							Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kPowerUsed);
							return false;
						}

						if (bHasResource && !bBlockWhileShouting)
						{
							return true;
						}

						return false;
					}

				case RE::MagicSystem::SpellType::kLesserPower:
					{
						if (a_this->actor->IsInCastPowerList(a_spell->As<RE::SpellItem>()))
						{
							return false;
						}

						if (bHasResource && !bBlockWhileShouting)
						{
							return true;
						}

						return false;
					}

				case RE::MagicSystem::SpellType::kWortCraft:
					{
						if (a_alchStrength)
						{
							if (a_spell->IsFood())
							{
								*a_alchStrength = 0.0f;
							}
							else
							{
								auto AlchemyValue = a_this->actor->GetActorValue(RE::ActorValue::kAlchemy);
								*a_alchStrength = RE::MagicFormulas::GetWortcraftEffectStrength(AlchemyValue);
							}
						}

						return true;
					}

				case RE::MagicSystem::SpellType::kVoicePower:
					{
						if (bBlockShoutRecovery || bBlockMulticasting || bBlockWhileSCasting)
						{
							return false;
						}

						if (a_this->state.get() == RE::MagicCaster::State::kCharging &&
						    a_this->actor->IsCurrentShout(a_spell->As<RE::SpellItem>()) &&
						    a_this->actor->IsInCastPowerList(a_spell->As<RE::SpellItem>()))
						{
							Utils::SafeSet(a_reason, RE::MagicSystem::CannotCastReason::kPowerUsed);
							return false;
						}

						return true;
					}

				case RE::MagicSystem::SpellType::kScroll:
					{
						if (!bBlockMulticasting && !bBlockWhileShouting)
						{
							return true;
						}

						return false;
					}

				default:
					return true;
			}
		}

		static void Update(RE::ActorMagicCaster* a_this, float a_delta)
		{
			Update_Impl(a_this, a_delta);
			if (!a_this->castingArt)
			{
				RE::BSAnimationUpdateData updateData{};
				updateData.deltaTime = a_delta;
				updateData.flags = static_cast<std::uint16_t>(0x1000000);
				updateData.unk2C = true;
				updateData.unk2E = true;
				a_this->UpdateAnimationGraphManager(updateData);
			}

			a_this->UpdateImpl(a_delta);
		}

		static void Update_Impl(RE::ActorMagicCaster* a_this, float a_delta)
		{
			a_this->CheckAttachCastingArt();
			if (!a_this->currentSpell || !a_this->actor)
			{
				return;
			}

			auto bIsPlayer = a_this->actor == RE::PlayerCharacter::GetSingleton();
			if (a_this->state.get() == RE::MagicCaster::State::kCasting &&
			    a_this->currentSpell->GetCastingType() == RE::MagicSystem::CastingType::kConcentration)
			{
				if (a_this->currentSpell->GetDelivery() == RE::MagicSystem::Delivery::kAimed)
				{
					if (bIsPlayer && ((a_this->projectileTimer - a_delta) <= 0.0f))
					{
						a_this->actor->ProcessVATSAttack(
							a_this,
							false,
							nullptr,
							a_this->castingSource == RE::MagicSystem::CastingSource::kLeftHand);
					}
				}
				else
				{
					RE::MagicItem::SkillUsageData SkillUsageData{};
					if (a_this->currentSpell->GetSkillUsageData(SkillUsageData))
					{
						if (!SkillUsageData.custom)
						{
							a_this->actor->UseSkill(
								SkillUsageData.skill,
								SkillUsageData.magnitude * a_delta,
								nullptr);
						}
					}
				}
			}

			auto ResourceAcV = RE::MagicUtilities::GetAssociatedResource(a_this->currentSpell, a_this->castingSource);
			if (ResourceAcV != RE::ActorValue::kNone &&
			    (!bIsPlayer || !RE::PlayerCharacter::IsGodMode()) &&
			    a_this->flags.none(RE::ActorMagicCaster::Flags::kSkipCheckCast))
			{
				auto bUsesWhileCasting = RE::MagicUtilities::UsesResourceWhileCasting(a_this->currentSpell, a_this->castingSource);
				auto bUsesWhileCharging = RE::MagicUtilities::UsesResourceWhileCharging(a_this->currentSpell, a_this->castingSource);
				auto MagickaPool = Utils::GetActorValue(a_this->actor, ResourceAcV);
				auto MagickaCost = a_this->GetCurrentSpellCost();
				auto MagickaDiff = MagickaCost * a_delta;

				if (a_this->state.get() == RE::MagicCaster::State::kCasting && bUsesWhileCasting)
				{
					MagickaDiff = std::min(MagickaDiff, MagickaPool);
					if (MagickaDiff > 0.0f)
					{
						Utils::DamageActorValue(a_this->actor, ResourceAcV, -MagickaDiff);
					}
				}
				else if (a_this->state.get() == RE::MagicCaster::State::kUnk02 && bUsesWhileCharging)
				{
					if (!bUsesWhileCasting)
					{
						MagickaDiff /= a_this->currentSpell->GetChargeTime();
					}

					a_this->costCharged += MagickaDiff;
					if (!bUsesWhileCasting && a_this->costCharged > MagickaCost)
					{
						MagickaDiff -= (a_this->costCharged - MagickaCost);
						a_this->costCharged -= (a_this->costCharged - MagickaCost);
					}

					if ((MagickaCost - a_this->costCharged) <= MagickaPool)
					{
						Utils::DamageActorValue(a_this->actor, ResourceAcV, -MagickaDiff);
					}
					else
					{
						a_this->InterruptCast(false);
					}
				}
			}

			if (bIsPlayer)
			{
				auto& ReticuleController = RE::ReticuleController::GetSingleton();
				if (ReticuleController.data.size() == 0)
				{
					return;
				}

				// todo: REX
				if (GetTickCount64() < ReticuleController.nextUpdate)
				{
					return;
				}

				ReticuleController.nextUpdate = GetTickCount64() + 200;
				if (ReticuleController.data.back() != a_this->castingSource)
				{
					return;
				}

				RE::bhkPickData bhkPickData{};
				RE::NiPoint3 TargetLocation;
				RE::TESObjectCELL* TargetCell{ nullptr };
				a_this->FindPickTarget(TargetLocation, &TargetCell, bhkPickData);

				auto bValidPosition{ true };
				if (bhkPickData.unkC0 || !bhkPickData.rayOutput.rootCollidable)
				{
					bValidPosition = false;
				}
				else
				{
					auto MagicItemDataCollector = RE::MagicItemDataCollector{ a_this->currentSpell };
					a_this->currentSpell->Traverse(MagicItemDataCollector);

					std::uint32_t i{ 0 };
					do
					{
						if (i >= MagicItemDataCollector.projectileEffectList.size())
						{
							break;
						}

						auto Effect = MagicItemDataCollector.projectileEffectList[i++];
						bValidPosition = a_this->TestProjectilePlacement(*Effect, bhkPickData);
					}
					while (bValidPosition);
				}

				RE::HUDMenu::UpdateCrosshairMagicTarget(bValidPosition);
			}
		}

	public:
		static void InstallHooks()
		{
			REL::Relocation<std::uintptr_t> vtbl{ RE::VTABLE_ActorMagicCaster[0] };
			vtbl.write_vfunc(0x08, InterruptCastImpl);
			vtbl.write_vfunc(0x09, SpellCast);
			vtbl.write_vfunc(0x0A, CheckCast);
			vtbl.write_vfunc(0x1D, Update);

			{
				REL::Relocation<std::uintptr_t> target1{ RELOCATION_ID(33355, 34136), OFFSET(0x51, 0x51) };
				REL::Relocation<std::uintptr_t> target2{ RELOCATION_ID(33358, 34139), OFFSET(0xB9, 0xB9) };

				auto& trampoline = SKSE::GetTrampoline();
				trampoline.write_call<5>(target1.address(), InterruptCastHelper);
				trampoline.write_call<5>(target2.address(), InterruptCastHelper);
			}
		}
	};
}
