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

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpointLocation, PlayerViewpointRotation);
	/*UE_LOG(LogTemp, Warning, TEXT("Grabber reporting viewpoint %s %s"), *(PlayerViewpointLocation.ToString()), *(PlayerViewpointRotation.ToString()));*/


	
	FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerViewpointLocation, LineTraceEnd, 
		FColor(255, 0, 0), false, 0.0f, 0, 1.0f);

}

