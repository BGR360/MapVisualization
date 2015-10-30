//

#pragma once

#include "Class.h"
#include "LatLng.h"

/**
* Represents a bounding box on the Earth. The box is defined by a lower-left FLatLng
* and an upper-right FLatLng
*/
USTRUCT()
struct MAPVISUALIZATION_API FLatLngBounds
{
	GENERATED_USTRUCT_BODY()

	FLatLngBounds();
	FLatLngBounds(FLatLng LowerLeft, FLatLng UpperRight);
	~FLatLngBounds();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLatLng LowerLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLatLng UpperRight;
};