// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "IDSystemSave.generated.h"

/**
 * 
 */
UCLASS()
class ACTOR_IDENTIFIER_API UIDSystemSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "IDSystem")
	class UIDSystemInstance* GameInstance;
};
