// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OpenStreetMap.generated.h"

/**
 * Place an OpenStreetMap Actor into the world to visualize a .osm XML file.
 * Call LoadFromXml() to initialize the map from a file. This will read the file
 * and generate all of the necessary OpenStreetNodes and OpenStreetWays.
 */
UCLASS()
class MAPVISUALIZATION_API AOpenStreetMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenStreetMap();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// TODO: Stub out interface
	
};
