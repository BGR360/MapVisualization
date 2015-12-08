// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Map.h"

#include "OpenStreetMap.generated.h"

class UMapProjectionComponent;
class UOpenStreetMapComponent;
class URoadGraphComponent;
class UOpenStreetMapFile;

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

    // Called when the Actor is destroyed
    virtual void Destroyed() override;

    // Get MapProjection
    UFUNCTION(BlueprintPure, Category = Map)
    UMapProjectionComponent* GetProjection();

    // Get the Map Component
    UFUNCTION(BlueprintPure, Category = Map)
    UOpenStreetMapComponent* GetMap();
    
    // Generates a network of pink debug lines that draws the Nodes and Ways
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Drawing)
    void DrawMap() const;

private:
    // The MapProjection used to convert Nodes' LatLng positions to 3D World coordinates
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    UMapProjectionComponent* Projection;

    // The component that holds all of the OSM file's data
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    UOpenStreetMapComponent* Map;

    // The Road Graph that represents all the Intersections and RoadSegments on the Map
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RoadGraph, meta = (AllowPrivateAccess = "true"))
    URoadGraphComponent* RoadGraph;

    // For the purposes of drawing/erasing the map at the proper times in the editor,
    // We keep track of the last Map we had
    UOpenStreetMapFile* LastMap;

    // TODO Have a Quadtree of Nodes

    // Utility function for erasing all debug lines
    void EraseDebugLines() const;
};
