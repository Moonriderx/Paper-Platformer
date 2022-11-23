// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableStaticMeshComponent.h"

UMovableStaticMeshComponent::UMovableStaticMeshComponent()
{

}

void UMovableStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
}

void UMovableStaticMeshComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMovableStaticMeshComponent::Move(bool bTriggered)
{
}

void UMovableStaticMeshComponent::OnMove()
{
}

void UMovableStaticMeshComponent::OnMoveFinished()
{
}

void UMovableStaticMeshComponent::UpdateRotation(float CurveValue)
{
}

void UMovableStaticMeshComponent::UpdateLocation(float CurveValue)
{
}
