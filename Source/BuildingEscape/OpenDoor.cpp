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
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
 	// float CurrentYaw = FMath::Lerp(CurrentRotation.Yaw, InitialYaw + TargetYaw, 0.04f);
