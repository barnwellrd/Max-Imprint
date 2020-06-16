#pragma once

#include <Logger/Logger.h>
#include <API/UE/Containers/FString.h>
#include <fstream>
#include <Permissions.h>
 
namespace MI {
	TArray<uint64> adminArray;

	bool IsAdmin(uint64 steam_id) {
		return adminArray.Contains(steam_id);
	}

	void LoadNppPermissionsArray() {
		adminArray.Empty();
		adminArray.Append(Permissions::GetGroupMembers("Admins"));
	}

	// Continuously update admins list
	void RecurringLoadNppPermissionsArray() {
		API::Timer::Get().RecurringExecute(&MI::LoadNppPermissionsArray, 30, -1, true);
	}
}
