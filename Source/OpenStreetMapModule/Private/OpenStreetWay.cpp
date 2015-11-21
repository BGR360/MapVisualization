// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetWay.h"
#include "OpenStreetNode.h"


// Sets default values
FOpenStreetWay::FOpenStreetWay() : Id(0), Nodes(), bIsHighway(false), HighwayName(TEXT("")), NumLanes(-1)
{
}

FOpenStreetWay::~FOpenStreetWay()
{
}

// Compares a Node to an int32 Id Key
bool FOpenStreetWay::operator==(int32 const& other)
{
    return Id == other;
}