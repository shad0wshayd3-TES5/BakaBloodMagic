#pragma once

namespace BloodMagic
{
	class Settings
	{
	public:
		class General
		{
		public:
			inline static bool bBloodMagicActive{ true };
			inline static bool bGraveRobberDefault{ true };
		};
		
		class Modifiers
		{
		public:
			inline static float fBloodMagicCostScale{ 5.0f };
			inline static float fBloodMagicDurationScale{ 1.0f };
			inline static float fBloodMagicMagnitudeScale{ 1.0f };
			inline static float fBloodMagicStepRate{ 10.0f };
			inline static float fBloodMagicStepDurationScale{ 0.05f };
			inline static float fBloodMagicStepMagnitudeScale{ 0.05f };
		};

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

		static void Update()
		{
			if (m_FirstRun)
			{
				m_FirstRun = false;
			}

			m_ini_base.LoadFile(BASE_INI);
			m_ini_user.LoadFile(USER_INI);

			// General
			GetModSettingBool("General", "bBloodMagicActive", General::bBloodMagicActive);
			GetModSettingBool("General", "bGraveRobberDefault", General::bGraveRobberDefault);

			// Modifiers
			GetModSettingFloat("Modifiers", "fBloodMagicCostScale", Modifiers::fBloodMagicCostScale);
			GetModSettingFloat("Modifiers", "fBloodMagicDurationScale", Modifiers::fBloodMagicDurationScale);
			GetModSettingFloat("Modifiers", "fBloodMagicMagnitudeScale", Modifiers::fBloodMagicMagnitudeScale);
			GetModSettingFloat("Modifiers", "fBloodMagicStepRate", Modifiers::fBloodMagicStepRate);
			GetModSettingFloat("Modifiers", "fBloodMagicStepDurationScale", Modifiers::fBloodMagicStepDurationScale);
			GetModSettingFloat("Modifiers", "fBloodMagicStepMagnitudeScale", Modifiers::fBloodMagicStepMagnitudeScale);

			// GraveRobber
			GraveRobber::Load();

			// Reset
			m_ini_base.Reset();
			m_ini_user.Reset();
		}

		inline static bool m_FirstRun{ true };

	private:
		static void GetModSettingBool(const std::string& a_section, const std::string& a_setting, bool& a_value)
		{
			auto base = m_ini_base.GetBoolValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetBoolValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = user;
		}

		static void GetModSettingFloat(const std::string& a_section, const std::string& a_setting, float& a_value)
		{
			auto base = m_ini_base.GetDoubleValue(a_section.c_str(), a_setting.c_str(), a_value);
			auto user = m_ini_user.GetDoubleValue(a_section.c_str(), a_setting.c_str(), base);
			a_value = static_cast<float>(user);
		}

		inline static CSimpleIniA m_ini_base{ true };
		inline static CSimpleIniA m_ini_user{ true };

		inline static constexpr char BASE_INI[] = "Data/MCM/Config/BloodMagic/settings.ini" ;
		inline static constexpr char USER_INI[] = "Data/MCM/Settings/BloodMagic.ini";
	};
}
