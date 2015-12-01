// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Map.h"

#include "OpenStreetMap.generated.h"

class UMapProjectionComponent;
class UOpenStreetMapComponent;

/**
 * A Visualization of an OpenStreetMapFile Asset.
 */
UCLASS()
class MAPVISUALIZATION_API AOpenStreetMap : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AOpenStreetMap();
    
    // The width of the road lines
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drawing)
    float RoadWidth;
    
    // The default color for all Ways, if they're not roads
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drawing)
    FColor DefaultWayColor;
    
    // The color of the road lines
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drawing)
    FColor RoadColor;

    // Called whenever the Construction Script is called (UPROPERTY changes, etc.)
    virtual void OnConstruction(const FTransform& Transform) override;

    // Get MapProjection
    UFUNCTION(BlueprintPure, Category = Map)
    UMapProjectionComponent* GetProjection();
    
    // Generates a network of pink debug lines that draws the Nodes and Ways
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Drawing)
    void DrawMap() const;
    
    // Checks to see if there has been a change in values
    // TODO Remove when we move DrawMap to the construction script
    void CheckForChangedDrawValues();

private:
    // The MapProjection used to convert Nodes' LatLng positions to 3D World coordinates
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    UMapProjectionComponent* Projection;

    // The .osm xml file Asset
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    UOpenStreetMapComponent* Map;

    // TODO Have a Quadtree of Nodes
};
