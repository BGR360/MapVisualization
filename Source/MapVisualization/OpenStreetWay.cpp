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

// Add Node
// Automatically updates the Way's appearance in the world.
void FOpenStreetWay::AddNode(FOpenStreetNode* Node)
{
    Nodes.Push(Node);
}

// Remove Node
// @return The number of nodes removed
int32 FOpenStreetWay::RemoveNode(FOpenStreetNode* Node)
{
    int32 numRemoved = Nodes.Remove(Node);
    return numRemoved;
}
