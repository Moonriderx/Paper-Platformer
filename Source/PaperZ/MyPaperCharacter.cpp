// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"


AMyPaperCharacter::AMyPaperCharacter()
{
	OnCharacterMovementUpdated.AddDynamic(this, &AMyPaperCharacter::Animate);

	bReplicates = true;

	GetCapsuleComponent()->SetCapsuleRadius(70.f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(138.f);

	GetSprite()->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));
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

	if (!IsPlayerControlled()) // is this a player controlled actor
	{
		UWorld* World = GetWorld();
		if (World)
		{
			APlayerController* PlayerController = World->GetFirstPlayerController(); // this will return the local player controller
			if (PlayerController)
			{
				ACharacter* Character = PlayerController->GetCharacter(); // get the character out of it
				if (Character)
				{
					Character->CalcCamera(DeltaTime, ViewInfo.Emplace()); // get the information of the camera's location - specifically rotation
				}
			}
		}
	}

	/*Everytime we move animate is called and we first call that*/
	SetCurrentAnimationDirection(OldVelocity, ViewInfo);
		
	if (OldVelocity.Size() > 0.0f)
	{
		switch (CurrentAnimationDirection)
		{
		case AnimationDirection::Up:
			GetSprite()->SetFlipbook(FB.WalkUp);
			break;
		case AnimationDirection::Down:
			GetSprite()->SetFlipbook(FB.WalkDown);
			break;
		case AnimationDirection::Left:
			GetSprite()->SetFlipbook(FB.WalkLeft);
			break;
		case AnimationDirection::Right:
			GetSprite()->SetFlipbook(FB.WalkRight);
			break;
		case AnimationDirection::UpLeft:
			GetSprite()->SetFlipbook(FB.WalkUpLeft);
			break;
		case AnimationDirection::UpRight:
			GetSprite()->SetFlipbook(FB.WalkUpRight);
			break;
		case AnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(FB.WalkDownLeft);
			break;
		case AnimationDirection::DownRight:
			GetSprite()->SetFlipbook(FB.WalkDownRight);
			break;

		default:
			break;
		}
	}
	else
	{
		switch (CurrentAnimationDirection)
		{
		case AnimationDirection::Up:
			GetSprite()->SetFlipbook(FB.IdleUp);
			break;
		case AnimationDirection::Down:
			GetSprite()->SetFlipbook(FB.IdleDown);
			break;
		case AnimationDirection::Left:
			GetSprite()->SetFlipbook(FB.IdleLeft);
			break;
		case AnimationDirection::Right:
			GetSprite()->SetFlipbook(FB.IdleRight);
			break;
		case AnimationDirection::UpLeft:
			GetSprite()->SetFlipbook(FB.IdleUpLeft);
			break;
		case AnimationDirection::UpRight:
			GetSprite()->SetFlipbook(FB.IdleUpRight);
			break;
		case AnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(FB.IdleDownLeft);
			break;
		case AnimationDirection::DownRight:
			GetSprite()->SetFlipbook(FB.IdleDownRight);
			break;

		default:
			break;
		}
	}

}

void AMyPaperCharacter::SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo)
{

	if (!ViewInfo.IsSet()) return;
	const FVector Forward = UKismetMathLibrary::GetForwardVector(ViewInfo.GetValue().Rotation); 
	const FVector Right = UKismetMathLibrary::GetRightVector(ViewInfo.GetValue().Rotation);
	const float ForwardSpeed = FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(), Forward) * 100) / 100;
	const float RightSpeed = FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(), Right) * 100) / 100;

}

