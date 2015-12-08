// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Intersection.h"
#include "RoadSegment.h"
#include "Runtime/Core/Public/Containers/Array.h"

/**
 * The RoadGraph stores a collection of Intersections and Roads.
 * As opposed to OpenStreetMap's Nodes and Ways, the RoadGraph is less
 * detailed and more suited for algorithms dealing with graphs.
 */
class ROADGRAPHMODULE_API RoadGraph
{
public:
	RoadGraph();
	~RoadGraph();

    TArray<Intersection>* GetIntersections();
    TArray<RoadSegment>* GetRoadSegments();

private:
    // All of the Intersections in the RoadGraph
    TArray<Intersection> Intersections;

    // All of the RoadSegments in the RoadGraph
    TArray<RoadSegment> RoadSegments;
};
