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

	// ...
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
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	// set the door rotation
	Owner->SetActorRotation(NewRotation);

}

void UOpenDoor::CloseDoor()
{
	// find the owning actor
	AActor *Owner = GetOwner();
	// create a rotation
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	// set the door rotation
	Owner->SetActorRotation(NewRotation);

}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume every frame
	// if the opening actor is in the volume, open the door
	if (PressurePlate->IsOverlappingActor(OpeningActor))
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

