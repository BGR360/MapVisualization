// Fill out your copyright notice in the Description page of Project Settings.

#include "GeographicLibModule.h"
#include "GeographicLibWrapper.h"

// Sets the default values
FGeographicLibWrapper::FGeographicLibWrapper()
{
}

// Converts a FLatLng EarthPos to a FVector WorldPos
FVector FGeographicLibWrapper::TransverseMercatorProject(FLatLng EarthPos, FLatLng Center) const
{
    return FVector();
}

// Converts a FVector WorldPos to a FLatLng EarthPos
FLatLng FGeographicLibWrapper::TransverseMercatorProject(FVector WorldPos, FLatLng Center) const
{
    return FLatLng();
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
