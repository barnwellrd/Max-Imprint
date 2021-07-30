#pragma once

inline void MaxImprintCommand(AShooterPlayerController* player) {
	if (!player || !player->PlayerStateField() || ArkApi::IApiUtils::IsPlayerDead(player))
		return;

	uint64 steamid = ArkApi::GetApiUtils().GetSteamIdFromController(player);
	uint64 playerTribeId = player->TargetingTeamField();

	AActor* Actor = player->GetPlayerCharacter()->GetAimedActor(ECollisionChannel::ECC_GameTraceChannel2, nullptr, 0.0, 0.0, nullptr, nullptr,
		false, false, false);

	if (Actor && Actor->IsA(APrimalDinoCharacter::GetPrivateStaticClass())) {
		APrimalDinoCharacter* dino = static_cast<APrimalDinoCharacter*>(Actor);
		const int dinoTribeId = dino->TargetingTeamField();

		//if player is in same tribe or an admin
		if ((playerTribeId == dinoTribeId && MI::IsAllowed(steamid)) || MI::IsAdmin(steamid)) {
			//if dino is a baby, player is an admin, or adult imprinting is allowed
			if (dino->bIsBaby()() || MI::IsAdmin(steamid) || MI::AllowAdultImprinting) {

				dino->UpdateImprintingQuality(1.0);

				ArkApi::GetApiUtils().SendNotification(player, FLinearColor(0.0, 1.0, 0.0, 0.0), 1.4f,
					10.0f, nullptr, "Dino Max Imprinted!");
			}
			else {
				ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4f,
					10.0f, nullptr, "Dino is not a baby!");
			}
		}
		else {
			ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4f,
				10.0f, nullptr, "Dino is not in your tribe!");
		}
	}
	else {
		ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4f,
			10.0f, nullptr, "Invalid target!");
	}
}

inline void ChatCommand(AShooterPlayerController* player, FString* message, int mode) {
	TArray<FString> parsed;
	message->ParseIntoArray(parsed, L" ", true);

	if (parsed.IsValidIndex(0)) {
		FString input = parsed[0];
		if (input.Compare(MI::ImprintCommand) == 0) {
			MaxImprintCommand(player);
		}
		else {
			ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4f,
				10.0f, nullptr, "Invalid chat command!");
		}
	}
	else {
		ArkApi::GetApiUtils().SendNotification(player, FLinearColor(1.0, 0.0, 0.0, 0.0), 1.4f,
			10.0f, nullptr, "Invalid chat command!");
	}
}


inline void InitChatCommands() {
	ArkApi::GetCommands().AddChatCommand(MI::ImprintCommand, &ChatCommand);
}

inline void RemoveChatCommands() {
	ArkApi::GetCommands().RemoveChatCommand(MI::ImprintCommand);
}

inline void InitCommands() {
	InitChatCommands();
}

inline void RemoveCommands() {	
	RemoveChatCommands();
}
