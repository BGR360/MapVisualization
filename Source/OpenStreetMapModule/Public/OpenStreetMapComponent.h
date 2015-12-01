// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenStreetMapComponent.generated.h"

/**
* Holds a reference to an OpenStreetMapFile Asset
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENSTREETMAPMODULE_API UOpenStreetMapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenStreetMapComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

    // The .osm file Asset
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Map)
    class UOpenStreetMapFile* MapFile;

    // Find Nodes
    // Returns nullptr if no Node with given Id exists in the Map
    // TODO Add HasNodeWithId() function (same for Ways)
    const FOpenStreetNode* FindNodeById(int32 Id) const;

    // TODO Find Nodes near LatLng/Vector with given radius

    // Find Ways
    // Returns nullptr if no Node with given Id exists in the Map
    const FOpenStreetWay* FindWayById(int32 Id) const;

    // TODO Find Ways near LatLng/Vector with given radius
};
