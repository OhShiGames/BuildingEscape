// Copyright of Iain Farrell

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// Setup (assumed) attached Physics Handle
	void SetupInputComponent();
	// Setup (assumed) attached Physics Handle
	void FindPhysicsHandle();
	// Ray-cast and grab what is in reach
	void Grab();
	void Release();
	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	// Get the FVector start point of the current location of the player
	const FVector GetReachLineStart();
	// Calculate the FVector end point that a raycast would reach, based on the current location of the player
	const FVector GetReachLineEnd();

	// how far the player can reach out
	float Reach = 100.f;
	
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;
};
