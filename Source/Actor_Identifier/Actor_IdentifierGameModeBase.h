// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Actor_IdentifierGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTOR_IDENTIFIER_API AActor_IdentifierGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	// virtual void BeginDestroy() override;
	// virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
