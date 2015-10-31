// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "LatLng.h"

#include "GeoComponent.generated.h"

/**
 * In order to display things that are tied to a particular position on Earth,
 * we must have an avenue to convert between Latitude/Longitude and UE4 units.
 * The pairing of UGeoComponent and UMapProjectionComponent achieves this.
 *
 * A GeoComponent should be added to every Actor that you want to represent
 * by a Latitude-Longitude position.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAPVISUALIZATION_API UGeoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeoComponent();

	// The location of the GeoComponent on Earth (latitude and longitude coordinates)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLatLng Location;
};
