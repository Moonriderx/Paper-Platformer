// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableStaticMeshComponent.h"

UMovableStaticMeshComponent::UMovableStaticMeshComponent()
{
	// by default the component is not set to tick. Need to be enabled
	PrimaryComponentTick.bCanEverTick = true;
}


void UMovableStaticMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoveCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishCallback;

		TimelineCallback.BindUFunction(this, FName("OnMove"));  // bind a current function
		TimelineFinishCallback.BindUFunction(this, FName("OnMoveFinished"));

		MoveTimeline.AddInterpFloat(MoveCurve, TimelineCallback);
		MoveTimeline.SetTimelineFinishedFunc(TimelineFinishCallback);
	}
}

void UMovableStaticMeshComponent::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

	if (bIsMoving)
	{
		MoveTimeline.TickTimeline(DeltaTime); // move the timeline along
	}
}


void UMovableStaticMeshComponent::Move(bool bTriggered)
{
	bIsTriggered = bTriggered;

	if (bTriggered)
	{
		MoveTimeline.PlayFromStart();
	}
	else
	{
		MoveTimeline.Reverse();
	}
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
