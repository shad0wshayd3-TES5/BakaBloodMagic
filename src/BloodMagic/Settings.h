#pragma once

namespace BloodMagic
{
	namespace Settings
	{
		namespace General
		{
			static REX::INI::Bool bBloodMagicActive{ "General", "bBloodMagicActive", true };
			static REX::INI::Bool bGraveRobberDefault{ "General", "bGraveRobberDefault", true };
		}

		namespace Modifiers
		{
			static REX::INI::F32 fBloodMagicCostScale{ "Modifiers", "fBloodMagicCostScale", 5.0f };
			static REX::INI::F32 fBloodMagicDurationScale{ "Modifiers", "fBloodMagicDurationScale", 1.0f };
			static REX::INI::F32 fBloodMagicMagnitudeScale{ "Modifiers", "fBloodMagicMagnitudeScale", 1.0f };
			static REX::INI::F32 fBloodMagicStepRate{ "Modifiers", "fBloodMagicStepRate", 10.0f };
			static REX::INI::F32 fBloodMagicStepDurationScale{ "Modifiers", "fBloodMagicStepDurationScale", 0.05f };
			static REX::INI::F32 fBloodMagicStepMagnitudeScale{ "Modifiers", "fBloodMagicStepMagnitudeScale", 0.05f };
		}

		/*
		class GraveRobber
		{
		public:
			static void Load()
			{
				auto section = General::bGraveRobberDefault
				                   ? m_ini_base.GetSection("GraveRobber")
				                   : m_ini_user.GetSection("GraveRobber");

				HealthMap.clear();
				for (auto& [entry, key] : *section)
				{
					HealthMap.emplace(atoi(entry.pItem), atoi(key));
				}
			}

			static void Save()
			{
				m_ini_user.LoadFile(USER_INI);
				m_ini_user.Delete("GraveRobber", nullptr, false);

				m_ini_user.SetBoolValue("General", "bGraveRobberDefault", true);
				for (auto& [fThreshold, fHealthMod] : GraveRobber::HealthMap)
				{
					auto ThresholdV = fmt::format(FMT_STRING("{:d}"), fThreshold);
					auto HealthModV = fmt::format(FMT_STRING("{:d}"), fHealthMod);
					m_ini_user.SetValue("GraveRobber", ThresholdV.c_str(), HealthModV.c_str());
				}

				m_ini_user.SaveFile(USER_INI, false);
				m_ini_user.Reset();
			}

			inline static std::map<std::int32_t, std::int32_t> HealthMap;
		};
		*/

		static void Update()
		{
			const auto ini = REX::INI::SettingStore::GetSingleton();
			ini->Init(
				"Data/MCM/Config/BloodMagic/settings.ini",
				"Data/MCM/Settings/BloodMagic.ini");
			ini->Load();

			// GraveRobber
			// GraveRobber::Load();
		}
	};
}
