// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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
	
	UE_LOG(LogTemp, Warning, TEXT( "%s Yaw: %f"), *Name, CurrentRotation.Yaw);
	if (IsValid(PressurePlate))
	{
		FString PlateName = PressurePlate->GetName();
		FVector PlateLocation = PressurePlate->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT( "%s Pos: %s"), *PlateName, *PlateLocation.ToString());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(PressurePlate) && IsValid(ActorThatOpen) && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{

		OpenDoor(DeltaTime);	
	}
}
 	// float CurrentYaw = FMath::Lerp(CurrentRotation.Yaw, InitialYaw + TargetYaw, 0.04f);
void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (YawAlpha >= 1) 
	{
		return;
	}
	YawAlpha += OpenSpeed * DeltaTime;
	float CurrentYaw = FMath::Lerp(InitialYaw, InitialYaw + TargetYaw, YawAlpha);
	CurrentRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(CurrentRotation);
}