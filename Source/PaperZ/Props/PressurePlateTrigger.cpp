// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlateTrigger.h"

// Sets default values
APressurePlateTrigger::APressurePlateTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APressurePlateTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlateTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

