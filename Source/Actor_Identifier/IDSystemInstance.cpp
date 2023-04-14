// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "IDSystemInstance.h"
#include "IDSystem.h"

#include <climits>

void UIDSystemInstance::AddID(AActor* newActor, int32& newID) {
	if ( newActor && !(IdentifiedActors.Contains(newID)) ) {
		IdentifiedActors.Add(newID, newActor);
	}
}

void UIDSystemInstance::Load() {

	for (auto& SavedActor : IdentifiedActors) {
		int32 ID = SavedActor.Key;
		AActor* Actor = SavedActor.Value;

		UIDSystem* IDComponent = Actor->FindComponentByClass<UIDSystem>();
		if (IDComponent)
		{
			if (IDComponent->IsIdentified()) {
				IDComponent->MarkAsIdentified();
			}
			IDComponent->SetID(ID);
		}
	}
}

void UIDSystemInstance::Save() {
	// Get already saved actors
	TArray<AActor*> ActorsSaved;
	IdentifiedActors.GenerateValueArray(ActorsSaved);

	if (IdentifiedActors.Num() == 0) {
		UE_LOG(LogTemp, Display, TEXT("\n\n\n IdentifiedActors is empty.\n\n\n"));
	}

	// Find all actors
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), ActorsToFind);
	}

	// IDsChecked - lets to control how many unique IDs were checked.
	// It's made to prevent case when all possible ID`s captured.
	int32 IDsChecked = 1;

	for (AActor* Actor : ActorsToFind) {
		
		// Check whether found actor has IDSystem Component.
		UIDSystem* IDComponent = Actor->FindComponentByClass<UIDSystem>();

		if (IDComponent && IDComponent->IsIdentified())
		{
			// Check if we already saved current actor.
			if (ActorsSaved.Find(Actor) != INDEX_NONE && IdentifiedActors.Num() != 0) {
				// UE_LOG(LogTemp, Display, TEXT("\n\n\nCurrent actor is in Map so we skip it\n\n\n"));
				continue;
			}

			UE_LOG(LogTemp, Display, TEXT("\n\n\n IDSystem found!!!\n\n\n"));

			int32 newID = IDComponent->GetID();
			UE_LOG(LogTemp, Display, TEXT("\n\n\noldID = %d \n\n\n"), newID);

			// Check for the dublicating IDs.
			while (IdentifiedActors.Contains(newID)) {
				++newID;
				++IDsChecked;
				UE_LOG(LogTemp, Display, TEXT("\n\n\nnewID increment made \n\n\n"));

				// Prevent case where all IDs are captured.
				if (IDsChecked >= INT32_MAX) {
					return;
				}
				// If ID`s too big but still captured - start from the beggining.
				else if (newID >= INT32_MAX) {
					newID = 1;
				}
			}


			UE_LOG(LogTemp, Display, TEXT("\n\n\n SetID function call \n\n\n"));
			IDComponent->SetID(newID);

			UE_LOG(LogTemp, Display, TEXT("\n\n\nnewID = %d \n\n\n"), newID);
			AddID(Actor, newID);
		}
	}
}
