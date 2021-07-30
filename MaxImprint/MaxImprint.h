#pragma once

#include <Logger/Logger.h>
#include <API/UE/Containers/FString.h>
#include <fstream>
#include <ArkPermissions.h>
#include "json.hpp"

 
namespace MI {
	nlohmann::json config;

	TArray<uint64> adminArray;
	TArray<uint64> allowedArray;

	bool RequireGroupToImprint;
	FString AllowedGroup;
	bool AllowAdultImprinting;
	FString ImprintCommand;

	bool IsAdmin(uint64 steam_id) {
		return adminArray.Contains(steam_id);
	}

	bool IsAllowed(uint64 steam_id) {
		if (!MI::RequireGroupToImprint) {
			return true;
		}
		else {
			return allowedArray.Contains(steam_id);
		}
	}

	void LoadPermissionsArray() {
		adminArray.Empty();
		adminArray.Append(Permissions::GetGroupMembers("Admins"));

		allowedArray.Empty();
		allowedArray.Append(Permissions::GetGroupMembers(AllowedGroup));
	}

	// Continuously update admins list
	void RecurringLoadPermissionsArray() {
		API::Timer::Get().RecurringExecute(&MI::LoadPermissionsArray, 30, -1, true);
	}
}
