// Fill out your copyright notice in the Description page of Project Settings.

#include "section03_01.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty 1"));
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandler found in %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("No InputComponent found in %s"), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed 1"));
	auto Hit = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = Hit.GetComponent();
	AActor* actorHit = Hit.GetActor();
	if (actorHit != NULL) {
		//UE_LOG(LogTemp, Warning, TEXT("Actor Name hit:%s"), *(actorHit->GetName()));
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(),
			FRotator(0.0f, 0.0f, 0.0f)
		);
	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (PhysicsHandle->GrabbedComponent) {
		FVector PlayerViewpointLocation;
		FRotator PlayerViewpointRotation;
		FVector LineTraceEnd;
		GetReachLineEnd(PlayerViewpointLocation, PlayerViewpointRotation, LineTraceEnd);
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
		//UE_LOG(LogTemp, Warning, TEXT("Grabbed and move to %s"), *PhysicsHandle->GrabbedComponent->GetName());
	}

}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	FVector LineTraceEnd;
	GetReachLineEnd(PlayerViewpointLocation, PlayerViewpointRotation, LineTraceEnd);
	FHitResult Hit;
	FCollisionQueryParams collisionQueryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		Hit, PlayerViewpointLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		collisionQueryParams
	);
	return Hit;
}

void UGrabber::GetReachLineEnd(FVector& PlayerViewpointLocation, FRotator& PlayerViewpointRotation, FVector& LineTraceEnd){
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpointLocation, PlayerViewpointRotation);
	LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;
}
