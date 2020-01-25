// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRABBIT GRABBIT"));
	AActor* HitActor = GetFirstActorHit();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorHit: %s"), *HitActor->GetName());
	}
	// TODO only raycast when key is pressed
	// Try and reach any actors with physics body
	// if we hit something then attach to physics component
	// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("UNGRABBIT UNGRABBIT"));
	// TODO remove physics handle
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Yes physics handle on %s is %s"), *GetOwner()->GetName(), *PhysicsHandle->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("No physics handle on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComp = GetOwner()->InputComponent;
	if (InputComp)
	{
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

AActor* UGrabber::GetFirstActorHit()
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (!IsValid(MyPawn)) { return nullptr; }
	AController* MyCont = MyPawn->GetController();
	if (!MyCont) { return nullptr; }
	FVector ViewLoc; FRotator ViewRot;
	MyCont->GetPlayerViewPoint(OUT ViewLoc, OUT ViewRot);
	// UE_LOG(LogTemp, Warning, TEXT("Grabber ViewLoc: %s ViewRot: %s"), *ViewLoc.ToString(), *ViewRot.ToString());
	FVector LineEnd = ViewLoc + ViewRot.Vector() * Reach;
	// DrawDebugLine(GetWorld(), ViewLoc, LineEnd, FColor::Green, false, 1.f, 0, 5.f);
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewLoc, LineEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	AActor* ActorThatGotHit = Hit.GetActor();
	return ActorThatGotHit;
}