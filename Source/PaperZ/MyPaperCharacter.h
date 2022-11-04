// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Data.h"
#include "MyPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PAPERZ_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMyPaperCharacter();

protected:
		virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "PaperCharacter|Animation")
		void Animate(float DeltaTime, FVector OldLocation, const FVector OldVelocity);

	UFUNCTION(BlueprintCallable, Category = "PaperCharacter|Animation")
		virtual void SetCurrentAnimationDirectory(const FVector& Velocity);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperCharacter|Config")
		uint8 bIsMoving : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PaperCharacter|Config")
		AnimationDirection CurrentAnimationDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PaperCharacter|Config")
		Flipbooks FB;

	
};
