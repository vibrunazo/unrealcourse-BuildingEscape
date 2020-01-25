// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (!IsValid(MyPawn)) { return; }
	AController* MyCont = MyPawn->GetController();
	if (!MyCont) { return; }
	FVector ViewLoc; FRotator ViewRot;
	MyCont->GetPlayerViewPoint(OUT ViewLoc, OUT ViewRot);
	// UE_LOG(LogTemp, Warning, TEXT("Grabber ViewLoc: %s ViewRot: %s"), *ViewLoc.ToString(), *ViewRot.ToString());
	FVector LineEnd = ViewLoc + ViewRot.Vector() * Reach;
	// DrawDebugLine(GetWorld(), ViewLoc, LineEnd, FColor::Green, false, 1.f, 0, 5.f);
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewLoc, LineEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	AActor* ActorThatGotHit = Hit.GetActor();
	if (ActorThatGotHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorHit: %s"), *ActorThatGotHit->GetName());
	}
}

