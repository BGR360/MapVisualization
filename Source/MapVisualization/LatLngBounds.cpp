// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "LatLngBounds.h"

FLatLngBounds::FLatLngBounds()
{
}

FLatLngBounds::FLatLngBounds(FLatLng LowerLeft, FLatLng UpperRight)
    : LowerLeft(LowerLeft), UpperRight(UpperRight)
{
}

FLatLngBounds::~FLatLngBounds()
{
}
