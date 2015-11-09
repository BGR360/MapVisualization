// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenStreetElement.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "OpenStreetWay.generated.h"

/**
 * Represents a Way in an OpenStreetMap. A way is simply a list of Nodes and
 * could represent a road, a polygon, or a boundary.
 */
UCLASS()
class MAPVISUALIZATION_API AOpenStreetWay : public FOpenStreetElement
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AOpenStreetWay();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Add Node
    // Automatically updates the Way's appearance in the world.
    void AddNode(class FOpenStreetNode* Node);

    // Remove Node
    // Automatically updates the Way's appearance in the world.
    // @return The number of nodes removed
    int32 RemoveNode(FOpenStreetNode* Node);

    // Get Nodes
    TArray<FOpenStreetNode*>* GetNodes();

private:
    // The list of Nodes that are a part of this way
    TArray<FOpenStreetNode*> Nodes;
    
    // TODO Add Id to AOpenStreetWay
};
