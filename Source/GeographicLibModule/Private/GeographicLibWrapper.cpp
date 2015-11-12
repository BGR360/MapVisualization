// Fill out your copyright notice in the Description page of Project Settings.

#include "GeographicLibModule.h"
#include "GeographicLibWrapper.h"
#include "GeographicLibModule/Private/GeographicLib/TransverseMercator.hpp"

// Sets the default values
FGeographicLibWrapper::FGeographicLibWrapper()
{
}

// Converts a FLatLng EarthPos to a FVector WorldPos
FVector FGeographicLibWrapper::TransverseMercatorProject(FLatLng EarthPos, FLatLng Center) const
{
    Math::real x, y;
    TransverseMercator::UTM().Forward(ToReal(Center.Longitude),
                                      ToReal(EarthPos.Latitude),
                                      ToReal(EarthPos.Longitude),
                                      x, y);
    return FVector(ToFloat(x), ToFloat(y), 0.0);
}

// Converts a FVector WorldPos to a FLatLng EarthPos
FLatLng FGeographicLibWrapper::TransverseMercatorProject(FVector WorldPos, FLatLng Center) const
{
    Math::real lat, lon;
    TransverseMercator::UTM().Reverse(ToReal(Center.Longitude),
                                      ToReal(WorldPos.X),
                                      ToReal(WorldPos.Y),
                                      lat, lon);
    return FLatLng(ToFloat(lat), ToFloat(lon));
}

// Converts a float to the GeographicLib internal Math::real
Math::real FGeographicLibWrapper::ToReal(float Value) const
{
    return static_cast<Math::real>(Value);
}

// Converts the GeographicLib internal Math::real to a float
float FGeographicLibWrapper::ToFloat(Math::real Value) const
{
    return static_cast<float>(Value);
}
