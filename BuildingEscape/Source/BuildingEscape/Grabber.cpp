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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s: No InputComponent Found."), *GetOwner()->GetName());
	}

}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		// todo physics handle found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s: No PhysicsHandle Found."), *GetOwner()->GetName());
	}

}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// if the physics handle is attached
		/// move the object we're holding
}

void UGrabber::Grab()
{
	/// LINE TRACE: Try and reach any actors with physics body collision channel set

	/// if we hit something, attach a physics handle
	// todo attach physics handle
	this->GetFirstPhysicsBodyInReach();
}

void UGrabber::Release()
{
	// todo release physics handle
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player view point
	FVector PlayerVPLocation;
	FRotator PlayerVPRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerVPLocation, OUT PlayerVPRotation);

	FVector LineTraceEnd = PlayerVPLocation + (PlayerVPRotation.Vector() * Reach);
	if (false)
	{
		DrawDebugLine(GetWorld(), PlayerVPLocation, LineTraceEnd, FColor(200, 0, 0), false, 0.f, 0, 10.f);
	}
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
	return HitResult;
}
