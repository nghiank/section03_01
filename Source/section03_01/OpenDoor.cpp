// Fill out your copyright notice in the Description page of Project Settings.

#include "section03_01.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	actorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	owner = GetOwner();

	
}

void UOpenDoor::OpenDoor() {		
	owner->SetActorRotation(FRotator(0.f, 90.0f, 0.f));	
}

void UOpenDoor::CloseDoor() {
	owner->SetActorRotation(FRotator(0.f, 0.0f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (triggerVolume->IsOverlappingActor(actorThatOpen)) {
		OpenDoor();
		lastOpenDoorTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - lastOpenDoorTime > doorCloseDelay) {
		CloseDoor();
	}
}

