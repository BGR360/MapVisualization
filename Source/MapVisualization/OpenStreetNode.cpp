// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetNode.h"
#include "GeoComponent.h"


// Sets default values
FOpenStreetNode::FOpenStreetNode()
{
    Id = 0;
}

FOpenStreetNode::~FOpenStreetNode()
{
}

// Called when the game starts or when spawned
void FOpenStreetNode::BeginPlay()
{
    Super::BeginPlay();

}

// Get GeoComponent
UGeoComponent* FOpenStreetNode::GetGeoComponent() const
{
    return GeoComponent;
}

// Get Id
int64 FOpenStreetNode::GetId() const
{
    return Id;
}

void FOpenStreetNode::SetId(int64 Id)
{
    this->Id = Id;
}
