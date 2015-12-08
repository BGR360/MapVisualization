// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetNode.h"

// Sets default values
FOpenStreetNode::FOpenStreetNode() : Id(0), Location(), bIsEndOfWay(false)
{
}

FOpenStreetNode::FOpenStreetNode(int32 Id) : Id(Id), Location(), bIsEndOfWay(false)
{
}

FOpenStreetNode::FOpenStreetNode(int32 Id, FLatLng Location) : Id(Id), Location(Location), bIsEndOfWay(false)
{
}

FOpenStreetNode::~FOpenStreetNode()
{
}

// Compares a Node to an int32 Id Key
bool FOpenStreetNode::operator==(int32 const& other)
{
    return Id == other;
}
