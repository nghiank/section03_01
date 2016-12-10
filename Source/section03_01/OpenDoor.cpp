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

	if (GetTotalMassOfActorsOnPlate() > 50.0f) {
		OpenDoor();
		lastOpenDoorTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - lastOpenDoorTime > doorCloseDelay) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float totalMass = 0.0f;
	TArray<AActor*> overlappingActors;
	triggerVolume->GetOverlappingActors(overlappingActors);
	for (auto& actor : overlappingActors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Actor %s on pressure plate"), *actor->GetName());
	}
	return totalMass;
}