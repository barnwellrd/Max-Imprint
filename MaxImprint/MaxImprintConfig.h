#pragma once
#include <fstream>
#include <ArkPermissions.h>

inline void LoadConfig() {
	std::ifstream file(ArkApi::Tools::GetCurrentDir() + "/ArkApi/Plugins/MaxImprint/config.json");

	if (!file.is_open()) {
		return;
	}

	file >> MI::config;
	file.close();
	MI::RequireGroupToImprint = MI::config["General"]["RequireGroupToImprint"];
	MI::AllowedGroup = FString(ArkApi::Tools::Utf8Decode(MI::config["General"]["AllowedGroup"]).c_str());
	MI::AllowAdultImprinting = MI::config["General"]["AllowAdultImprinting"];
	MI::ImprintCommand = FString(ArkApi::Tools::Utf8Decode(MI::config["General"]["ImprintCommand"]).c_str());
}

inline void InitConfig() {
	LoadConfig();
}

