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

}

FOpenStreetNode UIntersection::GetOsmNode() const
{

}

int32 UIntersection::NumIncoming() const
{

}

int32 UIntersection::NumOutgoing() const
{

}

void UIntersection::AddIncoming(URoadSegment* NewIncoming)
{

}

void UIntersection::AddOutgoing(URoadSegment* NewOutgoing)
{

}

bool UIntersection::RemoveIncoming(URoadSegment* ToRemove)
{

}

bool UIntersection::RemoveOutgoing(URoadSegment* ToRemove)
{

}

TArray<URoadSegment*>& UIntersection::GetIncoming()
{

}

TArray<URoadSegment*>& UIntersection::GetOutgoing()
{

}
