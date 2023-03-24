// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Define root and sets its position for component list
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Sets component as root component
	SetRootComponent(Root);

	// Define root and sets its position for component list
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	// Sets attachment from mesh to root component
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	// ctrl shift p -> create implementation
	// UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));

	if(Mesh == nullptr) return;
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));


	//UGameplayStatics::PlaySoundAtLocation()

	// Allows us to get the pawn controller
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	
	// Checks for null ptr
	if (OwnerPawn == nullptr) return;

	// Stores the controller from pawn in variable
	AController* OwnerController = OwnerPawn->GetController();

	// Checks for null ptr
	if (OwnerController == nullptr) return;
	
	// Declare variables which will store positional/rotational data from player
	FVector Location;
	FRotator Rotation;

	// GetPlayerviewpoint will get camera view for player and eye-view for AI
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	// Stores location vector plus rotation unit vector times the max range of the projectile
	FVector End = Location + Rotation.Vector() * MaxRange;

	// Shows player camera position from which ray will start
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

	// Out Parameter for Line Trace function
	FHitResult Hit;
	// Ignore actor from shot
	FCollisionQueryParams Params;

	// Ignores shots fired from self
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// Creates and stores a line trace of the gun's bullet into a bool variable
	bool bSuccess(GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_GameTraceChannel1, Params));

	// If the line trace produces a sucessful hit:
	// 1.) Spawn particle system on the object that is hit
	// 2.) Inflict damage if the object is an actor
	if (bSuccess)
	{
		// Vector for shot direction, where the shot has come from
		FVector ShotOrigin = -Rotation.Vector();
		
		// Shows where the projectile has hit (debug particle effect)
		// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		
		// Spawn particle system when projectile impacts
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location , ShotOrigin.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		

		// Gets the actor from the hit result of our LineTrace
		AActor* HitActor = Hit.GetActor();

		// Calls UE TakeDamage function which applies damage to our affected actor
		if (HitActor != nullptr)
		{
			// Creates a Damage event to be used in our TakeDamage function
			FPointDamageEvent DamageEvent(DamageAmt, Hit, ShotOrigin, nullptr);
			
			// Calls derived class implementation of take damage function which does the following:
			// 1.) Removes damage appplied to players health
			// 2.) Prints how much health is left on the player that has been shot
			HitActor->TakeDamage(DamageAmt, DamageEvent, OwnerController, this);

		}

	}

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}