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

    // TODO Figure out what to do about int64 not being supported by Blueprints

    // Get Id
    int64 GetId() const;

    // Set Id
    void SetId(int64 Id);

private:
    // A Node has a Latitude-Longitude location, so we give it a GeoComponent

    // Every Node has an id
    UPROPERTY(VisibleAnywhere, Category = Map, meta = (AllowPrivateAccess = "true"))
    int64 Id;

    // Give the Node a billboard sprite so that it's visible in the World
    UPROPERTY(VisibleAnywhere, Category = Map, meta = (AllowPrivateAccess = "true"))
    class UMaterialBillboardComponent* BillboardComponent;
};
