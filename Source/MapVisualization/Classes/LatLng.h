// 

#pragma once

#include "Class.h"

USTRUCT()
struct FLatLng
{
	GENERATED_USTRUCT_BODY()

	FLatLng();
	FLatLng(float Latitude, float Longitude);

	UPROPERTY()
	float Latitude;

	UPROPERTY()
	float Longitude;
};