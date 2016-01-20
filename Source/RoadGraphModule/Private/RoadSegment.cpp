// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "RoadSegment.h"
#include "Intersection.h"

URoadSegment::URoadSegment() : Begin(nullptr), End(nullptr)
{
}

URoadSegment::~URoadSegment()
{
}

bool URoadSegment::IsValid() const
{
    return Begin != nullptr && End != nullptr;
}

UIntersection* URoadSegment::GetBegin() const
{
    return Begin;
}

UIntersection* URoadSegment::GetEnd() const
{
    return End;
}

void URoadSegment::SetBegin(UIntersection* NewBegin)
{
    // Remove this from the outgoing of the previous Begin
    // Update Begin
    Begin = NewBegin;
    // Add this to the outgoing of the new Begin
}

void URoadSegment::SetEnd(UIntersection* NewEnd)
{
    // Remove this from the incoming of the previous End
    // Update End
    End = NewEnd;
    // Add this to the incoming of the new End
}
