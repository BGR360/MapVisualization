// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "MapProjectionComponent.h"
#include "GeographicLibModule/Public/GeographicLibWrapper.h"

// Sets default values for this component's properties
UMapProjectionComponent::UMapProjectionComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    bWantsBeginPlay = true;
    PrimaryComponentTick.bCanEverTick = true;

    Bounds = FLatLngBounds();
}

UMapProjectionComponent::UMapProjectionComponent(FLatLngBounds Bounds) : UMapProjectionComponent()
{
    SetBounds(Bounds);
}


// Called when the game starts
void UMapProjectionComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


// Called every frame
void UMapProjectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

// Get/Set Bounds
FLatLngBounds UMapProjectionComponent::GetBounds() const
{
    return Bounds;
}

void UMapProjectionComponent::SetBounds(FLatLngBounds Bounds)
{
    this->Bounds = Bounds;
}


// Position Conversion Functions

FLatLng UMapProjectionComponent::WorldToEarth(FVector WorldPos) const
{
    FGeographicLibWrapper GeoLibWrapper;
    return GeoLibWrapper.TransverseMercatorProject(WorldPos);
}

FVector UMapProjectionComponent::EarthToWorld(FLatLng EarthPos) const
{
    FGeographicLibWrapper GeoLibWrapper;
    return GeoLibWrapper.TransverseMercatorProject(EarthPos);
}

