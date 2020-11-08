// Copyright Joseph Leiferman 2020

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Checking for Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle has been found."));
	} 
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a PhysicsHandle Component"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));

	// Try and reach any actors with a phyics body collision channel set 
	FHitResult Hit = GetFirstPhysicsBodyInReach();

	// If we hit something then attach the physics handle.
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));

	// remove/release the physics handle
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get the palyers viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT PlayerViewPointLocation, 
																   OUT PlayerViewPointRotation);

	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FHitResult Hit;
	// Ray-cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld() -> LineTraceSingleByObjectType(
											OUT Hit,
											PlayerViewPointLocation,
											LineTraceEnd,
											FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
											TraceParams);

	AActor* ActorHit = Hit.GetActor();
	// Logging out to test
	if(ActorHit) 
	{
		UE_LOG(LogTemp, Warning, TEXT("The following actor is within reach: %s"), *ActorHit->GetName());
	}

	return Hit;
}

