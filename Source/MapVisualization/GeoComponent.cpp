// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "GeoComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "MapProjectionComponent.h"


// Sets default values for this component's properties
UGeoComponent::UGeoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

    Projection = nullptr;
}

// Get/Set Location

FLatLng UGeoComponent::GetLocation() const
{
    return Location;
}

void UGeoComponent::SetLocation(FLatLng Location)
{
    this->Location = Location;
    
    // Automatically update the World position when LatLng is changed
    ProjectLocationToWorld();
}

// Converts the Latitude-Longitude position to 3D position
// Sets the 3D position of the AActor we belong to
void UGeoComponent::ProjectLocationToWorld()
{
    // Check if we have a projection
    if (Projection)
    {
        // Get our parent's SceneComponent
        AActor* Parent = this->GetOwner();
        USceneComponent* ParentSceneComp = nullptr;
        
        // Check to see if there is a valid Parent
        if (Parent)
        {
            FVector NewPosition = Projection->ProjectToWorld(Location);
            Parent->SetActorLocation(NewPosition);
        }
    }
}