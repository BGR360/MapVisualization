// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapFile.h"

// Sets the default values
UOpenStreetMapFile::UOpenStreetMapFile()
{
    NextNodeId = 0;
    NextWayId = 0;
}

UOpenStreetMapFile::~UOpenStreetMapFile()
{
}

// Get/Set Bounds

FLatLngBounds UOpenStreetMapFile::GetBounds() const
{
    return Bounds;
}

void UOpenStreetMapFile::SetBounds(FLatLngBounds Bounds)
{
    this->Bounds = Bounds;
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
int32 UOpenStreetMapFile::ToSmallerNodeId(int64 LargeNodeId) const
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
int32 UOpenStreetMapFile::ToSmallerWayId(int64 LargeWayId) const
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

// Find Nodes
// Returns nullptr if no Node with given Id exists in the Map
const FOpenStreetNode* UOpenStreetMapFile::FindNodeById(int32 Id) const
{
    // Since we are numbering the Ids like 0, 1, 2, etc...
    // The Nodes array should already be sorted. So we can do a binary search
    int32 Begin = 0;
    int32 End = Nodes.Num() - 1;
    while (End - Begin > 0)
    {
        int32 Guess = Begin + (End - Begin) / 2;
        int32 GuessId = Nodes[Guess].Id;
        if (Id < GuessId)
        {
            End = Guess;
        }
        else if (Id > GuessId)
        {
            Begin = Guess + 1;
        }
        else
        {
            return &Nodes[Guess];
        }
    }

    return nullptr;
}

// Find Ways
// Returns nullptr if no Node with given Id exists in the Map
const FOpenStreetWay* UOpenStreetMapFile::FindWayById(int32 Id) const
{
    // Since we are numbering the Ids like 0, 1, 2, etc...
    // The Ways array should already be sorted. So we can do a binary search
    int32 Begin = 0;
    int32 End = Ways.Num() - 1;
    while (End - Begin > 0)
    {
        int32 Guess = Begin + (End - Begin) / 2;
        int32 GuessId = Ways[Guess].Id;
        if (Id < GuessId)
        {
            End = Guess;
        }
        else if (Id > GuessId)
        {
            Begin = Guess;
        }
        else
        {
            return &Ways[Guess];
        }
    }

    return nullptr;
}

// Finds where exactly the given Node is inside the given Way (its index in the Way)
// Returns INDEX_NONE if given Node is not in the given Way
int32 UOpenStreetMapFile::IndexOfNodeInWay(int32 NodeId, int32 WayId) const
{
    const FOpenStreetWay* Way = FindWayById(WayId);
    return Way->Nodes.Find(NodeId);
}

// Get center of Bounds
FLatLng UOpenStreetMapFile::GetBoundsCenter() const
{
    float LatDiff = Bounds.UpperRight.Latitude - Bounds.LowerLeft.Latitude;
    float LonDiff = Bounds.UpperRight.Longitude - Bounds.LowerLeft.Longitude;
    float CenterLat = Bounds.LowerLeft.Latitude + (LatDiff / 2.0);
    float CenterLon = Bounds.LowerLeft.Longitude + (LonDiff / 2.0);
    return FLatLng(CenterLat, CenterLon);
}

// Check if a LatLng point is inside the Map's bounds
bool UOpenStreetMapFile::IsInBounds(FLatLng Point) const
{
    return (Point.Latitude > Bounds.LowerLeft.Latitude) &&
        (Point.Latitude < Bounds.UpperRight.Latitude) &&
        (Point.Longitude > Bounds.LowerLeft.Longitude) &&
        (Point.Longitude < Bounds.UpperRight.Longitude);
}
