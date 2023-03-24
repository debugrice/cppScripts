// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

//#include "SkinnedMeshComponent.generated.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Initializes health variable so that it starts at max health
	Health = MaxHealth;


	Gun = GetWorld()->SpawnActor<AGun>(GunClass); //Initial spawning of Gun
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); // Hide initial gun that came with mesh
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket")); // Attach gun to player
	Gun->SetOwner(this); // Set owner of Gun to ShooterCharacter

	
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up keys for movement based on project settings -> engine -> input
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput); // Pitch for looking in Y direction
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput); // Yaw for looking in X Direction

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate); // Controller aiming framerate adjustment for looking in Y direction
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate); // Controller aiming framerate adjustment for looking in X direction

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &AShooterCharacter::MoveForward); // Move in forward direction
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight); // move in right direction
	
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,this, &AShooterCharacter::Jump); //Utilize jump function defined in source code, Action for IE_Pressed utilization
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed,this, &AShooterCharacter::Shoot); // Utilize pull trigger script in gun.cpp to fire gun on left button pressed

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{

	// stores take damage method which 
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// If Health is lower than the damage to apply, no further damage will be applied. 
	DamageToApply = FMath::Min(Health, DamageToApply);
	
	// Decrement Health by damage to apply amount
	Health -= DamageToApply;

	// Print remaining player health 
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		// Remove the ability to move/shoot from player once they have died
		DetachFromControllerPendingDestroy();
		// Remove Capsule Collider from player once dead
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	// ForwardVector in the amount that the project setting axis value is set to => 1.0
	AddMovementInput(GetActorForwardVector() * AxisValue);

}

void AShooterCharacter::MoveRight(float AxisValue)
{
	// RightVector in the amount the project setting axis value is set to => 1.0
	AddMovementInput(GetActorRightVector()*AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue*RotationRate*GetWorld()->DeltaTimeSeconds);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue*RotationRate*GetWorld()->DeltaTimeSeconds);
}

void AShooterCharacter::Shoot()
{
	// When the shoot function is called the gun class method PullTrigger is activated, which does the following:
	// Spawns a particle effect on gun end and on the impact point
	// Activates a TakeDamage method
	Gun->PullTrigger();
}

// void AShooterCharacter::LookUp(float AxisValue)
// {
//  // This function does nothing, calls function with same parameter for axis value
//  // Easier to call parent class AddControllerPitchInput from bind axis
// 	AddControllerPitchInput(AxisValue);
// }


