// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoadSegment.generated.h"

struct FIntersection;

/**
 * A RoadSegment is a path between two intersections.
 * A RoadSegment is strictly one-way.
 */
USTRUCT()
struct ROADGRAPHMODULE_API FRoadSegment
{
    GENERATED_USTRUCT_BODY()

    FRoadSegment();
    ~FRoadSegment();

    FIntersection* Begin;
    FIntersection* End;
};
