// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperZ/Components/MovableStaticMeshComponent.h"
#include "PaperZ/Interface/InteractableInterface.h"
#include "MovingStaticMeshBaseActor.generated.h"


// This is going to represents our doors, our windows, etc.. The moveable objects itself

UCLASS()
class PAPERZ_API AMovingStaticMeshBaseActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingStaticMeshBaseActor();

	virtual FName GetInteractTag_Implementation() override;
	virtual void Interact_Implementation(bool bInteracting) override;

	bool IsDisabled() const { return bIsDisabled; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Moving Actor")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Moving Actor")
	UMovableStaticMeshComponent* MovableMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	FName InteractTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Moving")
	bool bIsDisabled;

};
