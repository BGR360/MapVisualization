// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenStreetElement.h"
#include "LatLng.h"
#include "OpenStreetNode.generated.h"

/**
 * Represents a Node in an OpenStreetMap. A Node is simply a point on a map,
 * it could be part of a road, the corner of square, or a stop sign.
 */
USTRUCT()
struct OPENSTREETMAPMODULE_API FOpenStreetNode : public FOpenStreetElement
{
    GENERATED_USTRUCT_BODY()

public:
    FOpenStreetNode();
    FOpenStreetNode(int32 Id);
    FOpenStreetNode(int32 Id, FLatLng Location);
    ~FOpenStreetNode();
    
    // Every Node has an id
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|Node")
    int32 Id;

    // A Node has a Latitude-Longitude location
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|Node")
    FLatLng Location;
    
    // Compares a Node to an int32 Id Key
    bool operator==(int32 const& other);
};
