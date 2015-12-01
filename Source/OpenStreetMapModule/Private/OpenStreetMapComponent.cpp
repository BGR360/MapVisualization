// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapComponent.h"
#include "OpenStreetMapFile.h"


// Sets default values for this component's properties
UOpenStreetMapComponent::UOpenStreetMapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UOpenStreetMapComponent::BeginPlay()
{
	Super::BeginPlay();
}

