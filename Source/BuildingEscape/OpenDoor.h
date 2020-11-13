// Copyright Joseph Leiferman 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
    GENERATED_BODY()

public:	
    // Sets default values for this component's properties
    UOpenDoor();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void OpenDoor(float DeltaTime);
    void CloseDoor(float DeltaTime);
    float TotalMassOfActors() const;

private:

    float InitialYaw;
    float CurrentYaw;
    float DoorLastOpened = 0.f;
    bool SoundSwitch = false;

    UPROPERTY(EditAnywhere)
    UAudioComponent* AudioComponent = nullptr;

    UPROPERTY(EditAnywhere)
    float OpenDoorSpeed = 1.5f;
    
    UPROPERTY(EditAnywhere)
    float CloseDoorSpeed = 3.f;

    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = .5f;

    UPROPERTY(EditAnywhere)
    float OpenAngle = -90.f;

    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    float TriggerMass = 50.f;

    void FindAudioComponent();

    void ValidatePressurePlate() const;

};
