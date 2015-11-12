// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetWay.h"
#include "OpenStreetNode.h"


// Sets default values
FOpenStreetWay::FOpenStreetWay() : Id(0), Nodes()
{
}

FOpenStreetWay::FOpenStreetWay(int64 Id) : Id(Id), Nodes()
{
}

FOpenStreetWay::~FOpenStreetWay()
{
}