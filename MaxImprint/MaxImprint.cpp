#include <API/ARK/Ark.h>
#include <Timer.h>
#include "MaxImprint.h"
#include "MaxImprintCommands.h"
#include "MaxImprintConfig.h"

#pragma comment(lib, "ArkApi.lib")
#pragma comment(lib, "Permissions.lib")

void Init() {
	Log::Get().Init("MaxImprint");
	InitConfig();
	InitCommands();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		Init();

		// Timer to init Permission members array after Permission.dll has been loaded
		API::Timer::Get().DelayExecute(&MI::RecurringLoadPermissionsArray, 30);
		break;
	case DLL_PROCESS_DETACH:
		RemoveCommands();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
