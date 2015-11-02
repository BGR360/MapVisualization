// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetNode.h"
#include "GeoComponent.h"


// Sets default values
AOpenStreetNode::AOpenStreetNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    GeoComponent = CreateDefaultSubobject<UGeoComponent>(TEXT("GeoComponent"));
}

// Called when the game starts or when spawned
void AOpenStreetNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Get GeoComponent
UGeoComponent* AOpenStreetNode::GetGeoComponent() const
{
    return GeoComponent;
}
