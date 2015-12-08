// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "RoadGraph.h"

URoadGraph::URoadGraph()
{
}

URoadGraph::~URoadGraph()
{
}

TArray<FIntersection>* URoadGraph::GetIntersections()
{
    return &Intersections;
}

TArray<FRoadSegment>* URoadGraph::GetRoadSegments()
{
    return &RoadSegments;
}

void URoadGraph::AddIntersection(const FIntersection& NewIntersection)
{
    Intersections.Add(NewIntersection);
}

void URoadGraph::AddRoadSegment(const FRoadSegment& NewRoadSegment)
{
    RoadSegments.Add(NewRoadSegment);
}
