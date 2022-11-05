// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperCharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APaperCharacterPlayer::APaperCharacterPlayer()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	/** Spring Arm*/

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraSpringArm->SetupAttachment(GetCapsuleComponent());
	CameraSpringArm->TargetArmLength = 1500.f;
	CameraSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	CameraSpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->bInheritPitch = true;
	CameraSpringArm->bInheritYaw = true;
	CameraSpringArm->bInheritRoll = false;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->bEnableCameraRotationLag = true;
	CameraSpringArm->CameraLagSpeed = 4.f;
	CameraSpringArm->CameraRotationLagSpeed = 8.f;
	CameraSpringArm->CameraLagMaxDistance = 600.f;

	/** Camera*/

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm);
	Camera->FieldOfView = 55.f;
	Camera->PostProcessBlendWeight = 1.f;
	Camera->PostProcessSettings.bOverride_DepthOfFieldFstop = true;
	Camera->PostProcessSettings.DepthOfFieldFstop = 0.5f;
	Camera->PostProcessSettings.bOverride_DepthOfFieldSensorWidth = true;
	Camera->PostProcessSettings.DepthOfFieldSensorWidth = 100.f;
	Camera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	Camera->PostProcessSettings.DepthOfFieldFocalDistance = CameraSpringArm->TargetArmLength;
	Camera->PostProcessSettings.bOverride_DepthOfFieldMinFstop = true;
	Camera->PostProcessSettings.DepthOfFieldMinFstop = 0.f;
	Camera->PostProcessSettings.MotionBlurAmount = 0.f;
	


}

void APaperCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APaperCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/**Movement Controls */
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &APaperCharacterPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &APaperCharacterPlayer::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APaperCharacterPlayer::Jump);

	/** Camera Controls */
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APaperCharacterPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &APaperCharacterPlayer::Turn);


}

void APaperCharacterPlayer::SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo)
{


}

void APaperCharacterPlayer::MoveForward(float Value)
{
}

void APaperCharacterPlayer::MoveRight(float Value)
{
}

void APaperCharacterPlayer::LookUp(float Value)
{
}

void APaperCharacterPlayer::Turn(float Value)
{
}
