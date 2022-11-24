// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingStaticMeshBaseActor.h"

/** Door or whatever Static mesh component that we can interfere with */

// Sets default values
AMovingStaticMeshBaseActor::AMovingStaticMeshBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	MovableMesh = CreateDefaultSubobject<UMovableStaticMeshComponent>(TEXT("Movable Mesh"));
	MovableMesh->SetupAttachment(GetRootComponent());

}



// Called when the game starts or when spawned
void AMovingStaticMeshBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingStaticMeshBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName AMovingStaticMeshBaseActor::GetInteractTag_Implementation()
{
	return InteractTag;
}

void AMovingStaticMeshBaseActor::Interact_Implementation(bool bInteracting)
{
	if (!bIsDisabled)
	{
		MovableMesh->Move(bInteracting);
	}
}

