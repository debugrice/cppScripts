// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float TurnRate = 10.f;
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }
	
	bool bAlive = true;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
};
