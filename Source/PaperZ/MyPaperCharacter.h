// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Data.h"
#include "MyPaperCharacter.generated.h"

/**
This is the base character we are building from
 */
UCLASS()
class PAPERZ_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMyPaperCharacter();

protected:
		virtual void BeginPlay() override;
		virtual void OnJumped_Implementation() override;
		virtual void Landed(const FHitResult& Hit) override;
		virtual void NotifyJumpApex() override;

		// Movement Functions

		void ModifyJumpPower();
		void ResetJumpPower();

	UFUNCTION(BlueprintCallable, Category = "PaperCharacter|Animation")
		void Animate(float DeltaTime, FVector OldLocation, const FVector OldVelocity);

		virtual void SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperCharacter|Config")
		uint8 bIsMoving : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PaperCharacter|Config")
		AnimationDirection CurrentAnimationDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PaperCharacter|Config")
		Flipbooks FB;

	FTimerHandle JumpReset;
	int JumpCounter{};

	
};
