// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "IDSystem.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTOR_IDENTIFIER_API UIDSystem : public UActorComponent
{
	GENERATED_BODY()

private:
	// Identified variable tells the program wheter to show ID of current actor
	UPROPERTY(EditAnywhere, Category = "IDSystem")
		bool Identified = false;

	// ID - represent Unique ID of an actor
	UPROPERTY(EditAnywhere, Category = "IDSystem")
		int32 ID = 0;
public:	
	// Sets default values for this component's properties
	UIDSystem();

	// Setter for ID
	UFUNCTION(BlueprintCallable, Category = "IDSystem")
		void SetID(int32& newID);

	// Getter for ID
	UFUNCTION(BlueprintCallable, Category = "IDSystem")
		int32 GetID();

	// Getter for Identified
	UFUNCTION(BlueprintPure, Category = "IDSystem")
		bool IsIdentified() const;
	
	// Sets Identified as true
	void MarkAsIdentified();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
