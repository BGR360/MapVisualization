// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapFile.h"

// Sets the default values
UOpenStreetMapFile()
{
    NextNodeId = 0;
    NextWayId = 0;
}

~UOpenStreetMapFile()
{
}

// Get Nodes/Ways

TArray<FOpenStreetNode>* UOpenStreetMapFile::GetNodes()
{
    return &Nodes;
}

TArray<FOpenStreetWay>* UOpenStreetMapFile::GetWays()
{
    return &Ways;
}

// Add Node
// Returns a pointer to the new Node in the list
FOpenStreetNode* UOpenStreetMapFile::AddNode(int64 LargeId, FOpenStreetNode Node)
{
    Node.Id = NextNodeId;
    LargeToSmallNodeIds.Add(LargeId, NextNodeId);
    NextNodeId++;

    int32 Index = Nodes.Add(Node);
    return &Nodes[Index];
}

// Add Way
// Returns a pointer to the new Way in the list
FOpenStreetWay* UOpenStreetMapFile::AddWay(int64 LargeId, FOpenStreetWay Way)
{
    Way.Id = NextWayId;
    LargeToSmallWayIds.Add(LargeId, NextWayId);
    NextWayId++;

    int32 Index = Ways.Add(Way);
    return &Ways[Index];
}

// Returns the smaller int32 Id equivalent to the given int64 Id from the .osm file
int32 AOpenStreetMap::ToSmallerNodeId(int64 LargeNodeId) const
{
    const int32* SmallNodeId = LargeToSmallNodeIds.Find(LargeNodeId);
    if (SmallNodeId)
    {
        return *SmallNodeId;
    }
    else
    {
        return -1;
    }
}

// Returns the smaller int32 Id equivalent to the given int64 Id from the .osm file
int32 AOpenStreetMap::ToSmallerWayId(int64 LargeWayId) const
{
    const int32* SmallWayId = LargeToSmallWayIds.Find(LargeWayId);
    if (SmallWayId)
    {
        return *SmallWayId;
    }
    else
    {
        return -1;
    }
}
