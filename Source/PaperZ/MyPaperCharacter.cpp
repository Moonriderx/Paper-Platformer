// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"

AMyPaperCharacter::AMyPaperCharacter()
{
	OnCharacterMovementUpdated.AddDynamic(this, &AMyPaperCharacter::Animate);

	bReplicates = true;

	GetCapsuleComponent()->SetCapsuleRadius(70.f);

	GetSprite()->SetRelativeScale3D(FVector(11.f, 11.f, 11.f));
	GetSprite()->SetUsingAbsoluteRotation(true);
	GetSprite()->SetFlipbook(FB.IdleDown);
	GetSprite()->CastShadow = true;
}

void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
}

void AMyPaperCharacter::Animate(float DeltaTime, FVector OldLocation, const FVector OldVelocity)
{

	TOptional<FMinimalViewInfo> ViewInfo;

	/*Everytime we move animate is called and we first call that*/
	SetCurrentAnimationDirectory(OldVelocity, ViewInfo);
}

void AMyPaperCharacter::SetCurrentAnimationDirectory(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo)
{
}

