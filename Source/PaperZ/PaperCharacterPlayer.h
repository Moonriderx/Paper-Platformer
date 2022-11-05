// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPaperCharacter.h"
#include "PaperCharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;


/**
 * 
 */
UCLASS()
class PAPERZ_API APaperCharacterPlayer : public AMyPaperCharacter
{
	GENERATED_BODY()

public:
	APaperCharacterPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void LookUp(float Value);

	UFUNCTION()
	void Turn(float Value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "PlayerCharacter|Components")
		TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "PlayerCharacter|Components")
		TObjectPtr<UCameraComponent> Camera;
	
};
