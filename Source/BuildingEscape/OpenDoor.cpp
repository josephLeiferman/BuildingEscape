// Copyright Joseph Leiferman 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Math/Axis.h"

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

	float OpenDoorRotation = -90.f;

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw -= OpenDoorRotation;

	GetOwner()->SetActorRotation(CurrentRotation);

	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

