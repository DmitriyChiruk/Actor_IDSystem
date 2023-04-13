// Fill out your copyright notice in the Description page of Project Settings.


#include "IDSystem.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"

// Sets default values for this component's properties
UIDSystem::UIDSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UIDSystem::SetID(int32& newID) { 
	UE_LOG(LogTemp, Display, TEXT("\n\n\n SetID function: changing ID to %d "), newID);
	ID = (newID > 0)? newID: 0; 

	UE_LOG(LogTemp, Display, TEXT("ID value now = %d "), ID);
	
	UE_LOG(LogTemp, Display, TEXT("Trying to find TextRenderActor"));
	
	// Find Text attached to current actor and change it`s content to newID
	TArray<AActor*> Children;

	// Here was a mistake: I had to check ATTACHED actors, instead of CHILD
	GetOwner()->GetAttachedActors(Children);
	//GetOwner()->GetAllChildActors(Children);
	for (auto Element : Children) {
		ATextRenderActor* Text = Cast<ATextRenderActor>(Element);

		if (Text) {
			UE_LOG(LogTemp, Display, TEXT("TextRenderActor text changing"));
			Text->GetTextRender()->SetText(FText::FromString(FString::FromInt(ID)));
		}
	}
}

int32 UIDSystem::GetID() { return ID; }

bool UIDSystem::IsIdentified() const { return Identified;  }

void UIDSystem::MarkAsIdentified() {
	Identified = (ID > 0) ? true : false;
}

// Called when the game starts
void UIDSystem::BeginPlay()
{
	Super::BeginPlay();

	// If Identified - create a Text that have a value = ID and attach it to the actor.
	if (ID <= 0) {
		Identified = false;
	}
	if (Identified) {
		ATextRenderActor* Text = GetWorld()->SpawnActor<ATextRenderActor>(
												ATextRenderActor::StaticClass(), 
												FVector(0, 0, 120.f), 
												FRotator(0, 0, 0)
												);
		Text->GetTextRender()->SetText(FText::FromString(FString::FromInt(ID)));
		Text->GetTextRender()->SetTextRenderColor(FColor::Black);
		Text->SetActorScale3D(FVector(1.f, 1.f, 1.f));

		// Here was a mistake: I had to attach it to the actor, not to the component
		Text->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
		//Text->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	// ...
	
}


// Called every frame
void UIDSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

