// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* Tank; // How to access the -> Include tank file and GetPlayerPawn function
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 600.f;

	FTimerHandle FireRateTimerHandle;
	// UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();


};