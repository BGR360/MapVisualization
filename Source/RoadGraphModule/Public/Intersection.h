// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Containers/Array.h"

struct FOpenStreetNode;
struct RoadSegment;

/**
 * An Intersection is where multiple RoadSegments meet.
 * Intersections have incoming and outgoing RoadSegments.
 */
struct ROADGRAPHMODULE_API Intersection
{
    Intersection();
	~Intersection();

    // One Intersection should be located at a single OpenStreetNode
    FOpenStreetNode* OsmNode;

    // The RoadSegments that enter the Intersection
    TArray<RoadSegment*> Incoming;

    // The RoadSegments that leave the Intersection
    TArray<RoadSegment*> Outgoing;
};
