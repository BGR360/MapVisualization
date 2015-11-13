// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "LatLng.h"

FLatLng::FLatLng() : Latitude(0.0f), Longitude(0.0f)
{
}

FLatLng::FLatLng(float Latitude, float Longitude) : Latitude(Latitude), Longitude(Longitude)
{

}

FLatLng::~FLatLng()
{
}
