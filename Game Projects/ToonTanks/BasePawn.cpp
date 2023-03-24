// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
// #include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "Particles/ParticleSystem.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//The following lines assign and set attachments for components of BasePawn
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);// Attaches BaseMesh to Capsule Comp, a function of scene component

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDestruction()
{
	// This function is called on the destruction of the tank object (player index 0)

	// If the "DeathParticles" pointer is not null then when HandleDestruction is called, the "DeathParticle" particle System will be spawned at the tanks transform
	if (DeathParticles) // null ptr protection
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	// If the "DeathSound" pointer is not null then when HandleDestruction is called, the "DeathSound" SoundBase will be played at the tanks location
	if (DeathSound) // null ptr protection
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	// If the "DeathCameraShakeClass" pointer is not null then when HandleDestruction is called, the "DeathCameraShake" ShakeCamera will be played from the controller
	if (DeathCameraShakeClass) // null ptr protection
	{
		//UE 4.25 - ClientPlayCameraShake; UE 4.26+ ClientStartCameraShake
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathCameraShakeClass);
	}

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// When this function is called, the turret portion of the basePawn will rotate to a target
	// Stores the Vector from the turret mesh to the target (v2 - v1)
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	// Stores the yaw component of the ToTarget vector in order to only rotate about the z-axis
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	// Stores both roll and yaw component data in the event we want the the turet to rotate upwards
	// FRotator LookAtRotation = FRotator(ToTarget.Rotation().Roll, ToTarget.Rotation().Yaw, 0.f);

	//
	TurretMesh->SetWorldRotation(LookAtRotation);

}

void ABasePawn::Fire()
{


	// The following was used as debug logic to see whether or not the the fire 
	// function could spawn a debug sphere at the barrel-end of the turret 
	// when fired.

	//DrawDebugSphere(
	//	GetWorld(),
	//	ProjectileSpawnPoint->GetComponentLocation(),
	//	25.f,
	//	12,
	//	FColor::Red,
	//	false,
	//	.3f);

	// The following two variables are used to store location and rotation data of the 
	// the projectile spawn point into two variables
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	// Storing the projectile spawned into an "AProjectile" pointer
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	

	// Sets the projectile owner to basePawn class in order to disallow damage to basepawn by that projectile
	Projectile->SetOwner(this);

}
