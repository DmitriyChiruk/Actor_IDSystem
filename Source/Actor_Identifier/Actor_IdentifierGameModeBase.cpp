// Copyright Epic Games, Inc. All Rights Reserved.


#include "Actor_IdentifierGameModeBase.h"
#include "IDSystemInstance.h"
#include "IDSystemSave.h"
#include "Kismet/GameplayStatics.h"

#define SAVE_SLOT_NAME "GameSave"

void AActor_IdentifierGameModeBase::BeginPlay() {
	Super::BeginPlay();
	UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());

	GameInstance->LoadConfig();
	//GameInstance->Load();
	//GameInstance->Save();
	GameInstance->SaveConfig();
}

void AActor_IdentifierGameModeBase::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	LoadGameInstance();
	CurrentSave->GameInstance->Save();
}

void AActor_IdentifierGameModeBase::SaveGameInstance() {	
	/*
	if (!CurrentSave) {
		CurrentSave = Cast<UIDSystemSave>(UGameplayStatics::CreateSaveGameObject(UIDSystemSave::StaticClass()));
	}
	CurrentSave->GameInstance = GameInstance;
	*/

	UGameplayStatics::SaveGameToSlot(CurrentSave, SAVE_SLOT_NAME, 0);
}

void AActor_IdentifierGameModeBase::LoadGameInstance() {

	if (UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME, 0))
	{
		CurrentSave = Cast<UIDSystemSave>(UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, 0));
		CurrentSave->GameInstance->Load();
	}
	else {
		CurrentSave = Cast<UIDSystemSave>(UGameplayStatics::CreateSaveGameObject(UIDSystemSave::StaticClass()));
		CurrentSave->GameInstance = Cast<UIDSystemInstance>(GetWorld()->GetGameInstance());
		UE_LOG(LogTemp, Log, TEXT("Created New Save."));
	}
}

// void AActor_IdentifierGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason) {
void AActor_IdentifierGameModeBase::BeginDestroy() {
	/*
	UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());
	GameInstance->Save();
	*/
	SaveGameInstance();
	Super::BeginDestroy();

	/*
	if (GetGameInstance()) {
		UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());

		GameInstance->Save();
		GameInstance->SaveConfig();

		Super::BeginDestroy();
	}
	*/
}


