#include "BloodMagic/BloodMagic.h"

namespace
{
	void MessageCallback(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type)
		{
		case SKSE::MessagingInterface::kPostLoad:
			BloodMagic::InstallHooks();
			break;
		case SKSE::MessagingInterface::kDataLoaded:
			BloodMagic::Forms::Register();
			BloodMagic::Settings::Update();
			break;

		default:
			break;
		}
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	SKSE::AllocTrampoline(1 << 8);

	SKSE::GetMessagingInterface()->RegisterListener(MessageCallback);
	SKSE::GetPapyrusInterface()->Register(BloodMagic::Papyrus::Register);

	return true;
}
