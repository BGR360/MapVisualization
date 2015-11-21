// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LatLng.h"
#include "LatLngBounds.generated.h"

/**
 * Represents a bounding box for a map, with a lower-left hand LatLng position
 * and an upper-right hand LatLng position
 */
USTRUCT()
struct OPENSTREETMAPMODULE_API FLatLngBounds
{
    GENERATED_USTRUCT_BODY()

    FLatLngBounds();
    FLatLngBounds(FLatLng LowerLeft, FLatLng UpperRight);
    ~FLatLngBounds();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|LatLng")
    FLatLng LowerLeft;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map|LatLng")
    FLatLng UpperRight;
};
