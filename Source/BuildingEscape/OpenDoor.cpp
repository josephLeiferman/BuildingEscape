// Copyright Joseph Leiferman 2020

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Math/Axis.h"
#include "OpenDoor.h"

#define OUT

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
    InitialYaw  = GetOwner()->GetActorRotation().Yaw;
    CurrentYaw = InitialYaw;
    OpenAngle += InitialYaw;

    if(!PressurePlate) 
    {
        UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressurepalte set"), *GetOwner()->GetName());
    }
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (TotalMassOfActors() > TriggerMass)
    {
        OpenDoor(DeltaTime);
        DoorLastOpened = GetWorld()->GetTimeSeconds();
    }
    else
    {
        if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
        {
            CloseDoor(DeltaTime);
        }    
    }
}

void UOpenDoor::OpenDoor(float DeltaTime) 
{
    CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, OpenDoorSpeed);
    FRotator DoorRotation = GetOwner()->GetActorRotation();
    DoorRotation.Yaw = CurrentYaw;
    GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
    CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, CloseDoorSpeed);
    FRotator DoorRotation = GetOwner()->GetActorRotation();
    DoorRotation.Yaw = CurrentYaw;
    GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
    float TotalMass = 0.f;

    // Find all overlapping Actors.
    TArray<AActor*> OverlappingActors;

    if(!PressurePlate){return TotalMass;}
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);

    // Total the above masses
    for(AActor* Actor : OverlappingActors)
    {

        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }

    return TotalMass;
}



