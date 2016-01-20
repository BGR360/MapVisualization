// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "RoadGraph.h"
#include "Intersection.h"
#include "RoadSegment.h"

URoadGraph::URoadGraph()
{
}

URoadGraph::~URoadGraph()
{
}

/** Deletes all data so that a new RoadGraph can be generated */
void URoadGraph::Reset()
{
    Intersections.Empty();
    RoadSegments.Empty();
}

/** Instantiates a new UIntersection, adds it to this RoadGraph, and returns it */
UIntersection* URoadGraph::AddNewIntersection()
{
    UIntersection* NewIntersection = NewObject<UIntersection>();
    Intersections.Add(NewIntersection);
    return NewIntersection;
}

UIntersection* URoadGraph::AddNewIntersection(FOpenStreetNode* OsmNode)
{
    UIntersection* NewIntersection = AddNewIntersection();
    NewIntersection->SetOsmNode(OsmNode);
    return NewIntersection;
}

/** Instantiates a new URoadSegment, adds it to this RoadGraph, and returns it */
URoadSegment* URoadGraph::AddNewRoadSegment()
{
    URoadSegment* NewRoadSegment = NewObject<URoadSegment>();
    RoadSegments.Add(NewRoadSegment);
    return NewRoadSegment;
}

URoadSegment* URoadGraph::AddNewRoadSegment(UIntersection* Begin, UIntersection* End)
{
    URoadSegment* NewRoadSegment = AddNewRoadSegment();
    NewRoadSegment->SetBegin(Begin);
    NewRoadSegment->SetEnd(End);
    return NewRoadSegment;
}

TArray<UIntersection*>& URoadGraph::GetIntersections()
{
    return Intersections;
}

TArray<URoadSegment*>& URoadGraph::GetRoadSegments()
{
    return RoadSegments;
}
