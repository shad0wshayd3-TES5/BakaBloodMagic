#pragma once

#include "BloodMagic/ActiveEffect.h"
#include "BloodMagic/Actor.h"
#include "BloodMagic/ActorMagicCaster.h"
#include "BloodMagic/Forms.h"
#include "BloodMagic/HUDMenu.h"
#include "BloodMagic/Papyrus.h"
// #include "BloodMagic/MagicCaster.h"

namespace BloodMagic
{
	void InstallHooks()
	{
		BloodMagic::ActiveEffect::InstallHooks();
		BloodMagic::Actor::InstallHooks();
		BloodMagic::ActorMagicCaster::InstallHooks();
		BloodMagic::HUDMenu::InstallHooks();
		// BloodMagic::MagicCaster::InstallHooks();
	}
}
