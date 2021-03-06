// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/AudioComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	FString Name = GetOwner()->GetName();
	float MyFloat = 90;
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	InitialYaw = CurrentRotation.Yaw;
	// CurrentRotation.Yaw += 90;
	// GetOwner()->SetActorRotation(CurrentRotation);
	
	FindAudioComponent();
}

void UOpenDoor::PressurePlateLog()
{
	if (IsValid(PressurePlate))
	{
		FString PlateName = PressurePlate->GetName();
		FVector PlateLocation = PressurePlate->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT( "%s Pos: %s"), *PlateName, *PlateLocation.ToString());
	}

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no pressure plate"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (IsValid(PressurePlate) && IsValid(ActorThatOpen) && PressurePlate->IsOverlappingActor(ActorThatOpen))
	if (IsValid(PressurePlate) && TotalMassOfActors() >= MassToOpen)
	{
		OpenDoor(DeltaTime, OpenSpeed);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorCloseDelay)
		{
			OpenDoor(DeltaTime, -CloseSpeed);
		}
	}
}

void UOpenDoor::FindAudioComponent()
{
	AudioComp = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component!"), *GetOwner()->GetName());
	}
}
 	// float CurrentYaw = FMath::Lerp(CurrentRotation.Yaw, InitialYaw + TargetYaw, 0.04f);
void UOpenDoor::OpenDoor(float DeltaTime, float Speed)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (YawAlpha >= 1 && Speed > 0 || YawAlpha <= 0 && Speed < 0) 
	{
		return;
	}
	YawAlpha += Speed * DeltaTime;
	float CurrentYaw = FMath::Lerp(InitialYaw, InitialYaw + TargetYaw, YawAlpha);
	CurrentRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(CurrentRotation);

	if (LastSpeed != Speed)
	{
		AudioComp->Play();
		LastSpeed = Speed;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.0f;
	TArray<UPrimitiveComponent*> OverlappingComps;
	PressurePlate->GetOverlappingComponents(OUT OverlappingComps);

	for (auto &&Comp : OverlappingComps)
	{
		TotalMass += Comp->GetMass();
	}
	// UE_LOG(LogTemp, Warning, TEXT("TotalMass: %f"), TotalMass);
	return TotalMass;
}