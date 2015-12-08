// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Intersection.h"
#include "RoadSegment.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "RoadGraph.generated.h"

/**
 * The RoadGraph stores a collection of Intersections and Roads.
 * As opposed to OpenStreetMap's Nodes and Ways, the RoadGraph is less
 * detailed and more suited for algorithms dealing with graphs.
 */
UCLASS()
class ROADGRAPHMODULE_API URoadGraph : public UObject
{
    GENERATED_BODY()

public:
    URoadGraph();
    virtual ~URoadGraph();

    TArray<FIntersection>* GetIntersections();
    TArray<FRoadSegment>* GetRoadSegments();

    void AddIntersection(const FIntersection& NewIntersection);
    void AddRoadSegment(const FRoadSegment& NewRoadSegment);

private:
    // All of the Intersections in the RoadGraph
    UPROPERTY()
    TArray<FIntersection> Intersections;

    // All of the RoadSegments in the RoadGraph
    UPROPERTY()
    TArray<FRoadSegment> RoadSegments;
};
