// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IDSystemInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTOR_IDENTIFIER_API UIDSystemInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Map of Identified actors to be storred.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="IDSystem")
	TMap<int32, AActor*> IdentifiedActors;

	// Adds new element to IdentifiedActors
	UFUNCTION(BlueprintCallable, Category="IDSystem")
	void AddID(AActor* newActor, int32& newID);

	// Loads IdentifiedActors
	UFUNCTION(BlueprintCallable, Category = "IDSystem")
	void Load();

	// Scans for each actor that have IDSystem component and saves them to IdentifiedActors
	UFUNCTION(BlueprintCallable, Category = "IDSystem")
	void Save();
};
