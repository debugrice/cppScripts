// CopyRight Christopher Rice 2022

#include "Grabber.h"
#define OUT
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework//PlayerController.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	// Checking for Physics Handle Component
	GetPhysicsHandle();

	// Setup Keyboard Bindings
	SetupInputComponent(); 

	DrawDebugLine();
}




// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}

}

void UGrabber::Grab()
{

	UE_LOG(LogTemp, Warning, TEXT("Grabber used"));
	LineTrace();

	FHitResult HitResult = LineTrace();
	AActor* ActorHit = HitResult.GetActor();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }
		UE_LOG(LogTemp, Error, TEXT("Line trace has hit: %s"), *(ActorHit->GetName()));
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetPlayersReach());

	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) {return; }
	UE_LOG(LogTemp, Warning, TEXT("Release used"));
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::GetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

FVector UGrabber::GetPlayersReach()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Log for Location and Rotation:
	/*UE_LOG(LogTemp, Warning, TEXT("Location:%s, Rotation:%s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()*/
	//);
	return LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
}

FVector UGrabber::GetPlayersPosition()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);


	return LineTraceEnd = PlayerViewPointLocation;

}

void UGrabber::DrawDebugLine()
{
	//DrawDebugLine(
	//	GetWorld(),
	//	GetPlayersPosition(),
	//	GetPlayersReach(),
	//	FColor(0, 255, 0),
	//	false,
	//	0.f,
	//	0,
	//	5.f
	//);
}

FHitResult UGrabber::LineTrace()
{

	// Initialize Variables
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner()); // Ignore colisions with the owner 

	// Ray-cast out to a certain distance (Reach)
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersPosition(), 
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what it hits
	return Hit;
	
}