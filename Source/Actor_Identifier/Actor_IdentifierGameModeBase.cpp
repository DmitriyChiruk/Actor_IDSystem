// Copyright Epic Games, Inc. All Rights Reserved.


#include "Actor_IdentifierGameModeBase.h"
#include "IDSystemInstance.h"
#include "IDSystemSave.h"
#include "Kismet/GameplayStatics.h"

#define SAVE_SLOT_NAME "GameSave"

void AActor_IdentifierGameModeBase::BeginPlay() {
	Super::BeginPlay();
}

void AActor_IdentifierGameModeBase::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	LoadGameInstance();
	SaveGameInstance();
}

void AActor_IdentifierGameModeBase::SaveGameInstance() {	
	UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());
	GameInstance->Save();
	
	if (!CurrentSave) {
		CurrentSave = Cast<UIDSystemSave>(UGameplayStatics::CreateSaveGameObject(UIDSystemSave::StaticClass()));
	}
	CurrentSave->IdentifiedActors = GameInstance->IdentifiedActors;
	UGameplayStatics::SaveGameToSlot(CurrentSave, SAVE_SLOT_NAME, 0);
}

void AActor_IdentifierGameModeBase::LoadGameInstance() {

	if (UGameplayStatics::DoesSaveGameExist(SAVE_SLOT_NAME, 0))
	{
		CurrentSave = Cast<UIDSystemSave>(UGameplayStatics::LoadGameFromSlot(SAVE_SLOT_NAME, 0));
		UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());
		GameInstance->IdentifiedActors = CurrentSave->IdentifiedActors;
		GameInstance->Load();
	}
	else {
		CurrentSave = Cast<UIDSystemSave>(UGameplayStatics::CreateSaveGameObject(UIDSystemSave::StaticClass()));
		UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());
		GameInstance->Save();
		CurrentSave->IdentifiedActors = GameInstance->IdentifiedActors;
		UE_LOG(LogTemp, Log, TEXT("Created New Save."));
	}
}

/*
// void AActor_IdentifierGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason) {
void AActor_IdentifierGameModeBase::BeginDestroy() {
	UIDSystemInstance* GameInstance = Cast<UIDSystemInstance>(GetGameInstance());
	GameInstance->Save();
	SaveGameInstance();
	Super::BeginDestroy();
}
*/
