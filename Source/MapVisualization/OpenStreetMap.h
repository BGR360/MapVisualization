// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OpenStreetMap.generated.h"

/**
 * Place an OpenStreetMap Actor into the world to visualize a .osm XML file.
 * Call LoadFromXml() to initialize the map from a file. This will read the file
 * and generate all of the necessary OpenStreetNodes and OpenStreetWays.
 *
 * AOpenStreetMap does NOT actually store a TArray of AOpenStreetNode; all of
 * the nodes will be Attached to the RootComponent of the AOpenStreetMap
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

    // Get MapProjection
    UFUNCTION(BlueprintPure, Category = Map)
    class UMapProjectionComponent* GetProjection();

private:
    // The MapProjection used to convert GeoComponents' LatLng positions to 3D World coordinates
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    UMapProjectionComponent* Projection;
};
