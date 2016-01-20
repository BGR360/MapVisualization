// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "Intersection.h"

FIntersection::FIntersection() : OsmNode(nullptr)
{
}

FIntersection::FIntersection(FOpenStreetNode* Node) : OsmNode(Node)
{
}

FIntersection::~FIntersection()
{
}
