// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlateTrigger.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperZ/Interface/InteractableInterface.h"

// Sets default values
APressurePlateTrigger::APressurePlateTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	MovableMesh = CreateDefaultSubobject<UMovableStaticMeshComponent>(TEXT("Movable Mesh"));
	MovableMesh->SetupAttachment(BaseMesh);

	//OverlapComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Area"));
	//OverlapComponent->SetupAttachment(MovableMesh);

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Area"));
	OverlapComponent->SetupAttachment(MovableMesh);

}

// Called when the game starts or when spawned
void APressurePlateTrigger::BeginPlay()
{
	Super::BeginPlay();

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	OverlapComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
	
}

// Called every frame
void APressurePlateTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APressurePlateTrigger::Interact(bool bIsInteracting)
{
	TArray<AActor*> InteractableActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInteractableInterface::StaticClass(), InteractableActors);

	for (AActor* Actor : InteractableActors)
	{
		FName InteractTag = IInteractableInterface::Execute_GetInteractTag(Actor);
		for (FName Tag : TargetTags)
		{
			if (InteractTag.IsEqual(Tag, ENameCase::IgnoreCase))
			{
				IInteractableInterface::Execute_Interact(Actor, bIsInteracting);
			}
		}
	}
}

void APressurePlateTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsDisabled && !bIsTriggered)
	{
		MovableMesh->Move(true);
		Interact(true);

		bIsTriggered = true;
	}
}

void APressurePlateTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsDisabled)
	{
		MovableMesh->Move(false);
		Interact(false);

		bIsTriggered = false;
	}
}



