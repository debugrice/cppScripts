// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}
void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	// GetWorldTimerManager().SetTimer(FTimerHandle type var, user class to bind function, function address, how much time before function is called, looping boolean)
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}
	
	if (InFireRange() && Tank->bAlive) // Check for null ptr in Tank
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank) // Check for null ptr in Tank
	{
		// How to know if the tank is in range?
		// What is distance from tower to tank?
		// Vector from origin to location
		// GetActorLocation and Dist function - Returns distance between two points
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation()); //Finds distance between Tower and Tank

		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}