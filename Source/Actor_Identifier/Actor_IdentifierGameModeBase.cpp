// Copyright Epic Games, Inc. All Rights Reserved.


#include "Actor_IdentifierGameModeBase.h"
#include "IDSystemInstance.h"

void AActor_IdentifierGameModeBase::BeginPlay() {
	Super::BeginPlay();
	UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());

	GameInstance->LoadConfig();
	GameInstance->Load();
	GameInstance->Save();
	GameInstance->SaveConfig();
}

// void AActor_IdentifierGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason) {
/*
void AActor_IdentifierGameModeBase::BeginDestroy() {
	if (GetGameInstance()) {
		UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());

		GameInstance->Save();
		GameInstance->SaveConfig();

		Super::BeginDestroy();
	}
}
*/


