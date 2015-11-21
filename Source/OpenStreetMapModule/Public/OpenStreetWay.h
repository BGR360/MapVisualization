// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenStreetElement.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "OpenStreetNode.h"
#include "OpenStreetWay.generated.h"

/**
 * Represents a Way in an OpenStreetMap. A way is simply a list of Nodes and
 * could represent a road, a polygon, or a boundary.
 */
USTRUCT()
struct OPENSTREETMAPMODULE_API FOpenStreetWay : public FOpenStreetElement
{
    GENERATED_USTRUCT_BODY()

public:
    // Sets default values for this actor's properties
    FOpenStreetWay();
    ~FOpenStreetWay();
    
    // Every Way has an id (not unique from every Node's id)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|Way")
    int32 Id;
    
    // The list of Nodes that are a part of this way
    // TODO Refactor to a list of int32 Node Ids
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|Way")
    TArray<FOpenStreetNode> Nodes;
    
    // Denotes if the Way is a highway (a road)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|Way")
    bool bIsHighway;
    
    // If the Way is a highway, it may have a name.
    // It not a highway, string will be empty
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|Way")
    FString HighwayName;
    
    // If the Way is a highway, it may have a number of lanes.
    // If not a highway, NumLanes will be -1
    // TODO Refactor to RoadPriority
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|Way")
    int32 NumLanes;

    // Compares a Way to an int32 Id Key
    bool operator==(int32 const& other);
};
