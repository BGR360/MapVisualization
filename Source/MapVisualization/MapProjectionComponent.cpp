// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "MapProjectionComponent.h"


// Sets default values for this component's properties
UMapProjectionComponent::UMapProjectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMapProjectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMapProjectionComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

// Position Conversion Functions

FLatLng UMapProjectionComponent::ProjectToEarth(FVector2D MapPos) const
{
    return FLatLng();
}

FVector2D UMapProjectionComponent::ProjectToMap(FLatLng EarthPos) const
{
    return FVector2D();
}

FVector2D UMapProjectionComponent::ProjectToMap(FVector WorldPos) const
{
    return FVector2D();
}

FVector UMapProjectionComponent::ProjectToWorld(FVector2D MapPos) const
{
    return FVector();
}

FLatLng UMapProjectionComponent::ProjectToEarth(FVector WorldPos) const
{
    return FLatLng();
}

FVector UMapProjectionComponent::ProjectToWorld(FLatLng EarthPos) const
{
    return FVector();
}

