// Copyright of Iain Farrell

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.0f;
	float TimeOpened;

	UPROPERTY(EditAnywhere)
	float RequiredMass = 10.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	AActor *Owner;

	// Return total KG on triggerplate
	const float GetTotalMassOnPlate();
};
