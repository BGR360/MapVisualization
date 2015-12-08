// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "RoadGraphComponent.h"
#include "RoadGraph.h"


// Sets default values for this component's properties
URoadGraphComponent::URoadGraphComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Get/Set Osm Asset
UOpenStreetMapFile* URoadGraphComponent::GetOsmAsset()
{
    return OsmAsset;
}

void URoadGraphComponent::SetOsmAsset(UOpenStreetMapFile* NewOsmAsset)
{
    OsmAsset = NewOsmAsset;
}

// Generates the RoadGraph if a valid Osm Asset is present
void URoadGraphComponent::GenerateRoadGraph()
{
    // TODO Implement
}

