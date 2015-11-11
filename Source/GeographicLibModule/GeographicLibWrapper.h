// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MapVisualization/LatLng.h"

/**
 * A Wrapper for the necessary functionalities found in the GeographicLib
 * library. Currently, the necessary functionalities are:
 *
 * Transverse Mercator Map Projection
 */
class GEOGRAPHICLIBMODULE_API FGeographicLibWrapper
{
public:
    // Sets the default values
    FGeographicLibWrapper();
    
    // Converts a FLatLng EarthPos to a FVector WorldPos
    FVector TransverseMercatorProject(FLatLng EarthPos, FLatLng Center = FLatLng(0.0, 0.0)) const;
    
    // Converts a FVector WorldPos to a FLatLng EarthPos
    FLatLng TransverseMercatorProject(FVector WorldPos, FLatLng Center = FLatLng(0.0, 0.0)) const;
    
private:
    // TODO Converts a double to the GeographicLib internal Math::real
    
};