// Copyright Joseph Leiferman 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
    float Reach = 100.f;

	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UPROPERTY(EditAnywhere)
	UInputComponent* InputComponent = nullptr;
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	// Return the first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach();
	// Return the line trace end of the players reach
	FVector GetPlayersReach();
	// Get Player's Position in the world
	FVector GetPalyersWorldPos();
};
