// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenStreetElement.h"
#include "OpenStreetNode.generated.h"

/**
 * Represents a Node in an OpenStreetMap. A Node is simply a point on a map,
 * it could be part of a road, the corner of square, or a stop sign.
 */
UCLASS()
class MAPVISUALIZATION_API AOpenStreetNode : public AOpenStreetElement
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AOpenStreetNode();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Get GeoComponent
    UFUNCTION(BlueprintPure, Category = Map)
    class UGeoComponent* GetGeoComponent() const;

    // Get Id
    UFUNCTION(BlueprintPure, Category = Map)
    int32 GetId() const;

    // Set Id
    UFUNCTION(BlueprintCallable, Category = Map)
    void SetId(int32 Id);

private:
    // A Node has a Latitude-Longitude location, so we give it a GeoComponent
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    UGeoComponent* GeoComponent;

    // Every Node has an id
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    int32 Id;
};
