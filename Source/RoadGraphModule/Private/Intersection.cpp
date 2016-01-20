// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "Intersection.h"
#include "RoadSegment.h"

UIntersection::UIntersection() : OsmNode(nullptr)
{
}

UIntersection::~UIntersection()
{
}

bool UIntersection::IsValid() const
{
    return OsmNode != nullptr
        && (NumIncoming() > 0 || NumOutgoing() > 0);
}

FOpenStreetNode UIntersection::GetOsmNode() const
{
    return *OsmNode;
}

int32 UIntersection::NumIncoming() const
{
    return Incoming.Num();
}

int32 UIntersection::NumOutgoing() const
{
    return Outgoing.Num();
}

void UIntersection::AddIncoming(URoadSegment* NewIncoming)
{
    Incoming.Add(NewIncoming);
}

void UIntersection::AddOutgoing(URoadSegment* NewOutgoing)
{
    Outgoing.Add(NewOutgoing);
}

bool UIntersection::RemoveIncoming(URoadSegment* ToRemove)
{
    return Incoming.Remove(ToRemove) > 0;
}

bool UIntersection::RemoveOutgoing(URoadSegment* ToRemove)
{
    return Outgoing.Remove(ToRemove) > 0;
}

void UIntersection::SetOsmNode(FOpenStreetNode* NewNode)
{
    OsmNode = NewNode;
}

TArray<URoadSegment*>& UIntersection::GetIncoming()
{
    return Incoming;
}

TArray<URoadSegment*>& UIntersection::GetOutgoing()
{
    return Outgoing;
}
