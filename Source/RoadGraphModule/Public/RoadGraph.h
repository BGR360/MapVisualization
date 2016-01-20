// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Containers/Array.h"
#include "RoadGraph.generated.h"

class UIntersection;
class URoadSegment;
struct FOpenStreetNode;

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

    /** Deletes all data so that a new RoadGraph can be generated */
    void Reset();

    /** Instantiates a new UIntersection, adds it to this RoadGraph, and returns it */
    UIntersection* AddNewIntersection();
    UIntersection* AddNewIntersection(FOpenStreetNode* OsmNode);

    /** Instantiates a new URoadSegment, adds it to this RoadGraph, and returns it */
    URoadSegment* AddNewRoadSegment();
    URoadSegment* AddNewRoadSegment(UIntersection* Begin, UIntersection* End);

    TArray<UIntersection*>& GetIntersections();
    TArray<URoadSegment*>& GetRoadSegments();

private:
    // All of the Intersections in the RoadGraph
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<UIntersection*> Intersections;

    // All of the RoadSegments in the RoadGraph
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<URoadSegment*> RoadSegments;
};
