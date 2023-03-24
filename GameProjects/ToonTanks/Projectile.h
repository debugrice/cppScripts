// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UProjectileMovementComponent *ProjectileMovementComponent;

	//void OnHit(UPrimitiveCOmponent* component doing the hitting,
	// AActor* Actor getting hit,
	// UPrimitiveComponent* other component getting hit ie. static mesh,
	// physics engine applies impulse in reponse to collision, fvector is for direction/magnitude of this impulse
	// const FHitResult& access to hit result that has more information of the hit

	UFUNCTION() //Like uproperty but for functions
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* ProjectileTrail;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	// UE 4.25 - UCameraShake; UE 4.26+ UCameraShakeBase
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShake> HitCameraShakeClass;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
