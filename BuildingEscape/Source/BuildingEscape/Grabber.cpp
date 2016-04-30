// Copyright of Iain Farrell

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	/// look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {

	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: No PhysicsHandle Found."), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Get the player view point
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPLocation, OUT PlayerVPRotation);

	FVector LineTraceEnd = PlayerVPLocation + (PlayerVPRotation.Vector() * Reach);
	DrawDebugLine(GetWorld(), PlayerVPLocation, LineTraceEnd, FColor(200, 0, 0), false, 0.f, 0, 10.f);
	/// Raycast to reach distance
	FHitResult HitResult;
	auto collided = GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult, PlayerVPLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
		);
	/// see what we hit
	if (collided) {
		UE_LOG(LogTemp, Warning, TEXT("Collison: %s"), *HitResult.GetActor()->GetName());
	}
}

