// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenStreetElement.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "OpenStreetWay.generated.h"

/**
 * Represents a Way in an OpenStreetMap. A way is simply a list of Nodes and
 * could represent a road, a polygon, or a boundary.
 */
USTRUCT()
struct MAPVISUALIZATION_API FOpenStreetWay : public FOpenStreetElement
{
    GENERATED_USTRUCT_BODY()

public:
    // Sets default values for this actor's properties
    FOpenStreetWay();
    FOpenStreetWay(int64 Id);
    ~FOpenStreetWay();
    
    // Every Way has an id (not unique from every Node's id)
    UPROPERTY(VisibleAnywhere, Category = Map)
    int64 Id;
    
    // The list of Nodes that are a part of this way
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map)
    TArray<struct FOpenStreetNode*> Nodes;

    // Add Node
    //UFUNCTION(BlueprintCallable, Category = Map)
    void AddNode(struct FOpenStreetNode* Node);

    // Remove Node
    // @return The number of nodes removed
    //UFUNCTION(BlueprintCallable, Category = Map)
    int32 RemoveNode(FOpenStreetNode* Node);
};
