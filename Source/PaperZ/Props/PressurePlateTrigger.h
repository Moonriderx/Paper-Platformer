// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "PaperZ/Components/MovableStaticMeshComponent.h"
#include "PressurePlateTrigger.generated.h"


UCLASS()
class PAPERZ_API APressurePlateTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlateTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void Interact(bool bIsInteracting);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Trigger")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Trigger")
	UMovableStaticMeshComponent* MovableMesh;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Trigger")
	//USphereComponent* OverlapComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Trigger")
	UBoxComponent* OverlapComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
	bool bIsDisabled; // control the state of the pressurePlate

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
	bool bResetTrigger; // two situations: 1) pressureplate is staying down after activating; 2) pp is going up and resets after OnCollisonExit for example

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trigger")
	TArray<FName> TargetTags; // references of tags of actors that we want this pressureplate to affect in the world

private:
	bool bIsTriggered;

};
