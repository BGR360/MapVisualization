// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LatLng.generated.h"

/**
 * Represents a Latitude and Longitude position on the Earth
 */
USTRUCT()
struct MAPVISUALIZATION_API FLatLng
{
    GENERATED_USTRUCT_BODY()

    FLatLng();
    FLatLng(float Latitude, float Longitude);
    ~FLatLng();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Latitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Longitude;
};
