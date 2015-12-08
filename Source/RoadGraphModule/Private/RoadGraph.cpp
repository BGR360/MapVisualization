// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "RoadGraph.h"

RoadGraph::RoadGraph()
{
}

RoadGraph::~RoadGraph()
{
}

TArray<Intersection>* RoadGraph::GetIntersections()
{
    return &Intersections;
}

TArray<RoadSegment>* RoadGraph::GetRoadSegments()
{
    return &RoadSegments;
}

void RoadGraph::AddIntersection(const Intersection& NewIntersection)
{
    Intersections.Add(NewIntersection);
}

void RoadGraph::AddRoadSegment(const RoadSegment& NewRoadSegment)
{
    RoadSegments.Add(NewRoadSegment);
}
