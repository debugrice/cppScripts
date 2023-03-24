// CopyRight Christopher Rice 2022
#pragma once
#include "Components/AudioComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;
	float timer = 0.f;
	float TotalMass = 0.f;
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

	UPROPERTY(EditAnywhere)
	float OpenAngle;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float TotalMassToOpen;

	UPROPERTY()
	UAudioComponent * AudioComponent = nullptr;

	float GetOverlappingActorsMass() const;
	void FindAudioComponent();
	void FindPressurePlate();

};
