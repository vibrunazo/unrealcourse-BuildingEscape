// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float TotalMassOfActors() const;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void OpenDoor(float DeltaTime, float Speed);

private:
	UPROPERTY(EditAnywhere, Category="OpenDoor")
	float OpenSpeed = 0.3f;
	UPROPERTY(EditAnywhere, Category="OpenDoor")
	float CloseSpeed = 1.2f;
	UPROPERTY(EditAnywhere, Category="OpenDoor")
	float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere, Category="OpenDoor")
	float MassToOpen = 100.f;
	float InitialYaw;
	float YawAlpha = 0.f;
	UPROPERTY(EditAnywhere, Category="OpenDoor")
	ATriggerVolume* PressurePlate = nullptr;

	float DoorLastOpened = 0.f;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

};
