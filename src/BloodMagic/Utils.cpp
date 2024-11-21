#include "BloodMagic/Utils.h"

#include "TrueHUDAPI.h"

namespace BloodMagic
{
	bool Utils::FlashTrueHUDMeter(RE::Actor* a_actor, RE::ActorValue a_actorValue, bool a_long)
	{
		auto TrueHUDAPI = static_cast<TRUEHUD_API::IVTrueHUD4*>(TRUEHUD_API::RequestPluginAPI(TRUEHUD_API::InterfaceVersion::V4));
		if (!TrueHUDAPI)
		{
			return false;
		}

		TrueHUDAPI->FlashActorValue(a_actor->GetHandle(), a_actorValue, a_long);
		return true;
	}
}
