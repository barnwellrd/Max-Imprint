#pragma once

inline void MaxImprintCommand(AShooterPlayerController* player) {
	if (!player || !player->PlayerStateField() || ArkApi::IApiUtils::IsPlayerDead(player))
		return;

	uint64 steamid = ArkApi::GetApiUtils().GetSteamIdFromController(player);
	uint64 playerTribeId = player->TargetingTeamField();

	AActor* Actor = player->GetPlayerCharacter()->GetAimedActor(ECC_GameTraceChannel2, nullptr, 0.0, 0.0, nullptr, nullptr,
		false, false, false);

	if (Actor && Actor->IsA(APrimalDinoCharacter::GetPrivateStaticClass())) {
		APrimalDinoCharacter* dino = static_cast<APrimalDinoCharacter*>(Actor);
		const int dinoTribeId = dino->TargetingTeamField();

		//if player is in same tribe or an admin
		if (playerTribeId == dinoTribeId || MI::IsAdmin(steamid)) {
			//if dino is a baby or player is an admin
			if (dino->bIsBaby()() || MI::IsAdmin(steamid)) {

				dino->UpdateImprintingQuality(1.0);

				ArkApi::GetApiUtils().SendNotification(player, FLinearColor(0.0, 1.0, 0.0, 0.0), 1.4,
					10.0, nullptr, "Dino Max Imprinted!");
			}
			else {
				ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4,
					10.0, nullptr, "Dino is not a baby!");
			}
		}
		else {
			ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4,
				10.0, nullptr, "Dino is not in your tribe!");
		}
	}
	else {
		ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4,
			10.0, nullptr, "Invalid target!");
	}
}

inline void ChatCommand(AShooterPlayerController* player, FString* message, int mode) {
	TArray<FString> parsed;
	message->ParseIntoArray(parsed, L" ", true);

	if (parsed.IsValidIndex(0)) {
		FString input = parsed[0];
		if (input.Compare("/imprint") == 0) {
			MaxImprintCommand(player);
		}
		else {
			ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4,
				10.0, nullptr, "Invalid chat command!");
		}
	}
	else {
		ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4,
			10.0, nullptr, "Invalid chat command!");
	}
}


inline void InitChatCommands() {
	FString cmd1 = "/imprint";
	ArkApi::GetCommands().AddChatCommand(cmd1, &ChatCommand);
}

inline void RemoveChatCommands() {
	FString cmd1 = "/imprint";
	ArkApi::GetCommands().RemoveChatCommand(cmd1);
}

inline void InitCommands() {
	InitChatCommands();
}

inline void RemoveCommands() {	
	RemoveChatCommands();
}
