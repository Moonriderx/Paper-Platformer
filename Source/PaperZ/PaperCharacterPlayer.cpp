// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperCharacterPlayer.h"

APaperCharacterPlayer::APaperCharacterPlayer()
{

}

void APaperCharacterPlayer::BeginPlay()
{
}

void APaperCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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
