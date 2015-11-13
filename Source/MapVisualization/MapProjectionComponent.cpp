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
    DefaultHeight = 30.0f;
    ScaleFactor = 1.0f;
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

// Get center of Bounds
FLatLng UMapProjectionComponent::GetBoundsCenter() const
{
    float LatDiff = Bounds.UpperRight.Latitude - Bounds.LowerLeft.Latitude;
    float LonDiff = Bounds.UpperRight.Longitude - Bounds.LowerLeft.Longitude;
    float CenterLat = Bounds.LowerLeft.Latitude + (LatDiff / 2.0);
    float CenterLon = Bounds.LowerLeft.Longitude + (LonDiff / 2.0);
    return FLatLng(CenterLat, CenterLon);
}


// Position Conversion Functions

FLatLng UMapProjectionComponent::WorldToEarth(FVector WorldPos) const
{
    FGeographicLibWrapper GeoLibWrapper;
    
    // Get the center of the map's bounding box
    FLatLng CenterLatLng = GetBoundsCenter();
    
    // Reset the height of the WorldPos
    WorldPos.Z = 0.0;
    
    // Adjust the y position back to some big kilometer value by adding the y position of the CenterLatLng
    FVector CenterWorldPos = GeoLibWrapper.TransverseMercatorProject(CenterLatLng, CenterLatLng);
    WorldPos.Y += CenterWorldPos.Y;
    
    // Adjust by the ScaleFactor
    WorldPos /= ScaleFactor;
    
    // This will yield the proper x value, but the y value may be hundreds of kilometers north of the equator
    FLatLng EarthPos = GeoLibWrapper.TransverseMercatorProject(WorldPos, CenterLatLng);
    
    return EarthPos;
}

FVector UMapProjectionComponent::EarthToWorld(FLatLng EarthPos) const
{
    FGeographicLibWrapper GeoLibWrapper;
    
    // Get the center of the map's bounding box
    FLatLng CenterLatLng = GetBoundsCenter();
    
    // This will yield the proper x value, but the y value may be hundreds of kilometers north of the equator
    FVector WorldPos = GeoLibWrapper.TransverseMercatorProject(EarthPos, CenterLatLng);
    
    // Adjust for the y position by subtracting the y position of the CenterLatLng
    FVector CenterWorldPos = GeoLibWrapper.TransverseMercatorProject(CenterLatLng, CenterLatLng);
    WorldPos.Y -= CenterWorldPos.Y;
    
    // Adjust by the ScaleFactor
    WorldPos *= ScaleFactor;
    
    // Increase the height by the default offset
    WorldPos.Z += DefaultHeight;
    
    return WorldPos;
}

