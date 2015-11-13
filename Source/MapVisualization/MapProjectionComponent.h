// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenStreetMapModule/Public/LatLng.h"
#include "OpenStreetMapModule/Public/LatLngBounds.h"
#include "Runtime/Core/Public/Math/Vector.h"

#include "MapProjectionComponent.generated.h"

/**
 * The UMapProjectionComponent is in charge of managing the positions of every
 * Actor on a map. Each Actor with a UGeoComponent has a reference to a certain
 * UMapProjectionComponent which helps to convert its Latitude-Longitude
 * position to a UE4 3D position.
 *
 * In order to perform such conversions, a UMapProjectionComponent has a
 * FLatLngBounds object to localize its map projection.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAPVISUALIZATION_API UMapProjectionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    // Can choose to initialize with a bounding box
    UMapProjectionComponent();

    // Initializes the MapProjection with a bounding box
    UMapProjectionComponent(FLatLngBounds Bounds);
    
    // The default z-height for a point on the map (so they don't get hidden in the floor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drawing)
    float DefaultHeight;

    // Called when the game starts
    virtual void BeginPlay() override;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Get/Set the Map's Bounds
    UFUNCTION(BlueprintPure, Category = Projection)
    FLatLngBounds GetBounds() const;

    UFUNCTION(BlueprintCallable, Category = Projection)
    void SetBounds(FLatLngBounds Bounds);
    
    // Get center of Bounds
    FLatLng GetBoundsCenter() const;


    // Position Conversion Functions
    UFUNCTION(BlueprintCallable, Category = Projection)
    FLatLng WorldToEarth(FVector WorldPos) const;
    
    UFUNCTION(BlueprintCallable, Category = Projection)
    FVector EarthToWorld(FLatLng EarthPos) const;

private:
    // The bounding box of the map onto/from which we shall project
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    FLatLngBounds Bounds;
};
