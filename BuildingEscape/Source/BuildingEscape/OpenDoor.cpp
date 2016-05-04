// Copyright of Iain Farrell

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	this->Owner = GetOwner();
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s: No Pressure Plate assigned"), *this->Owner->GetName());
	}
}

void UOpenDoor::OpenDoor()
{
	this->Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	this->Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	auto CurrentTime = GetWorld()->GetTimeSeconds();
	// Poll the trigger volume every frame
	if (GetTotalMassOnPlate() >= RequiredMass)
	{
		OpenDoor();
		TimeOpened = CurrentTime;
	}
	else if (CurrentTime - TimeOpened > DoorCloseDelay)
	{
		CloseDoor();
	}
}

const float UOpenDoor::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	if (PressurePlate) {
		/// Find all the overlapping actors
		TArray<AActor*> OverlappingActors;
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);

		/// loop through them and total the mass
		for (const auto& OverlappingActor : OverlappingActors) {
			TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return TotalMass;
}