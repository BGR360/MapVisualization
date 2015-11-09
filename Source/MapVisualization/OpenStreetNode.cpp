// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetNode.h"
#include "GeoComponent.h"


// Sets default values
FOpenStreetNode::FOpenStreetNode() : Id(0), Location()
{
}

FOpenStreetNode(int64 Id) : Id(Id), Location()
{
}

FOpenStreetNode(int64 Id, FLatLng Location) : Id(Id), Location(Location)
{
}

FOpenStreetNode::~FOpenStreetNode()
{
}
