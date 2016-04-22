// Copyright of Iain Farrell

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	IsOpening = false;
	IsClosed = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	OpeningActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	// find the owning actor
	AActor *Owner = GetOwner();
	// create a rotation
	FRotator CurrentRotation = Owner->GetActorRotation();
	// currently assuming negative final yaw
	float CurrentYaw = CurrentRotation.Yaw;
	if (IsOpening && CurrentYaw <= OpenAngle) {
		float NewYaw = CurrentYaw - AngleDelta;
		NewYaw = NewYaw < OpenAngle ? OpenAngle : NewYaw;
		FRotator NewRotation = FRotator(0.0f, NewYaw, 0.0f);
		// set the door rotation
		Owner->SetActorRotation(NewRotation);
	}
	else {
		IsOpening = false;
	}
}

void UOpenDoor::CloseDoor()
{
	// find the owning actor
	AActor *Owner = GetOwner();
	FRotator CurrentRotation = Owner->GetActorRotation();
	// currently assuming negative final yaw
	float CurrentYaw = CurrentRotation.Yaw;
	if (!IsOpening && !IsClosed && CurrentYaw >= ClosedAngle) {
		float NewYaw = CurrentYaw + AngleDelta;
		NewYaw = NewYaw > ClosedAngle ? ClosedAngle : NewYaw;
		FRotator NewRotation = FRotator(0.0f, NewYaw, 0.0f);
		// set the door rotation
		Owner->SetActorRotation(NewRotation);
	}
	else {
		IsClosed = true;
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// Poll the trigger volume every frame
	// if the opening actor is in the volume, open the door
	if (PressurePlate->IsOverlappingActor(OpeningActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("opening: %d closed: %d"), IsOpening, IsClosed);
		IsOpening = true;
		IsClosed = false;
	}
	else
	{
		IsOpening = false;
	}

	if (IsOpening)
	{
		OpenDoor();
	}
	else if (!IsClosed)
	{
		CloseDoor();
	}
}

