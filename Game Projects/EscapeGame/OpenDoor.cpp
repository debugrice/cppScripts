// CopyRight Christopher Rice 2022


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;


	FindPressurePlate();
	FindAudioComponent();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	timer = GetWorld()->GetTimeSeconds();

	// UE_LOG(LogTemp, Warning, TEXT("Timer current time is %f"), timer);
	// UE_LOG(LogTemp, Warning, TEXT("The current time is %f"), DoorLastOpened);

	if ((GetOverlappingActorsMass() > TotalMassToOpen)) // Null Pointer protection (Pressure Plate is a pointer and if nothing is selected for this then unreal will crash because pointer will return with nothing)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("Door last opened current time is %f"), DoorLastOpened);


	}

	else
	{
		// if the door has been open longer than x seconds
		if (timer-DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor:: OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	FRotator DoorOpen = GetOwner()->GetActorRotation();
	DoorOpen.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorOpen);

	CloseDoorSound = false;
	if (!AudioComponent) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
		UE_LOG(LogTemp, Warning, TEXT("Open Sound is working"));
	}

}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime*DoorCloseSpeed);
	FRotator DoorClose = GetOwner()->GetActorRotation();
	DoorClose.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorClose);

	OpenDoorSound = false;
	if (!AudioComponent) {return; }
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
		UE_LOG(LogTemp, Warning, TEXT("Close Sound is working"));
	}


}

float UOpenDoor::GetOverlappingActorsMass() const
{
	float TotalMass = 0.f;
	TArray <AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate!"), *Actor->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("%f is current mass, you need %f to open the door"), TotalMass, TotalMassToOpen);


	}
	return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have an audio component"), *GetOwner()->GetName());
	}

}

void UOpenDoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the door component but does not have a pressure plate selected"), *GetOwner()->GetName());
	}

}