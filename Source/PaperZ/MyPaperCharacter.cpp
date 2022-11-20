// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


AMyPaperCharacter::AMyPaperCharacter()
{
	OnCharacterMovementUpdated.AddDynamic(this, &AMyPaperCharacter::Animate);

	GetCharacterMovement()->GravityScale = 2.8f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;

	bReplicates = true;

	GetCapsuleComponent()->SetCapsuleRadius(48.f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(98.f);

	GetSprite()->SetRelativeScale3D(FVector(3.5f, 3.5f, 3.5f));
	GetSprite()->SetUsingAbsoluteRotation(true);
	GetSprite()->SetFlipbook(FB.IdleDown);
	GetSprite()->CastShadow = true;
}

void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
}

void AMyPaperCharacter::OnJumped_Implementation()
{
	GetCharacterMovement()->bNotifyApex = true; // resets every single jump

	GetSprite()->SetPlayRate(0.f); // freezes the flipbooks, no running in place
	GetSprite()->SetPlaybackPositionInFrames(0, true);

	JumpCounter++;
	GetWorldTimerManager().ClearTimer(JumpReset);

	Super::OnJumped_Implementation();

}

void AMyPaperCharacter::Landed(const FHitResult& Hit)
{

	GetSprite()->SetPlayRate(1.f);
	GetCharacterMovement()->GravityScale = 2.8f;

	if (JumpCounter > 2)
	{
		ResetJumpPower();
	}

	ModifyJumpPower();
	GetWorldTimerManager().SetTimer(JumpReset, this, &AMyPaperCharacter::ResetJumpPower, 0.2f, false); // set a timer if .2 seconds passed, you missed the jump

}

void AMyPaperCharacter::NotifyJumpApex()
{

	GetCharacterMovement()->GravityScale = 5.f;

	Super::NotifyJumpApex();
}

void AMyPaperCharacter::ModifyJumpPower()
{

	switch (JumpCounter)
	{
	case 1:
		GetCharacterMovement()->JumpZVelocity = 1400.f;
		UE_LOG(LogTemp, Warning, TEXT("Jump Power Level 1"));
		break;
	case 2:
		GetCharacterMovement()->JumpZVelocity = 2000.f;
		UE_LOG(LogTemp, Warning, TEXT("Jump Power Level 2"));
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Jump Power Level 0"));
		break;
	}

}

void AMyPaperCharacter::ResetJumpPower()
{

	JumpCounter = 0;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	UE_LOG(LogTemp, Warning, TEXT("Jump Power Reset"));
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
	FVector Forward;
	FVector Right;
	if (ViewInfo.IsSet())
	{
		Forward = UKismetMathLibrary::GetForwardVector(ViewInfo.GetValue().Rotation);
		Right = UKismetMathLibrary::GetRightVector(ViewInfo.GetValue().Rotation);
	}
	else
	{
		Forward = GetActorForwardVector().GetSafeNormal();
		Right = GetActorRightVector().GetSafeNormal();
	}

	const float ForwardSpeed = FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(), Forward) * 100) / 100;
	const float RightSpeed = FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(), Right) * 100) / 100;


	bIsMoving = ForwardSpeed != 0.0f || RightSpeed != 0.0f;

	if (bIsMoving)
	{
		if (ForwardSpeed > 0.0f && abs(RightSpeed) < 0.5f)
		{
			CurrentAnimationDirection = AnimationDirection::Up;
		}
		else if (ForwardSpeed > 0.5f && RightSpeed >= 0.5f)
		{
			CurrentAnimationDirection = AnimationDirection::UpRight;
		}
		else if (ForwardSpeed > 0.5f && RightSpeed <= -0.5f)
		{
			CurrentAnimationDirection = AnimationDirection::UpLeft;
		}
		else if (ForwardSpeed < 0.5f && abs(RightSpeed) <= 0.5f)
		{
			CurrentAnimationDirection = AnimationDirection::Down;
		}
		else if (ForwardSpeed < -0.5f && RightSpeed >= 0.5f)
		{
			CurrentAnimationDirection = AnimationDirection::DownRight;
		}
		else if (ForwardSpeed < -0.5f && RightSpeed <= -0.5f)
		{
			CurrentAnimationDirection = AnimationDirection::DownLeft;
		}
		else if (abs(ForwardSpeed) < 0.5f && RightSpeed > 0.0f)
		{
			CurrentAnimationDirection = AnimationDirection::Right;
		}
		else
		{
			CurrentAnimationDirection = AnimationDirection::Left;
		}
	}
}

