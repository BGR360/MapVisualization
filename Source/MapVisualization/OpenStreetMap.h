// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "OpenStreetMapModule/Public/OpenStreetNode.h"
#include "OpenStreetMapModule/Public/OpenStreetWay.h"

#include "OpenStreetMap.generated.h"

class UMapProjectionComponent;
struct FOpenStreetNode;
struct FOpenStreetWay;

/**
 * Place an OpenStreetMap Actor into the world to visualize a .osm XML file.
 * Call LoadFromXml() to initialize the map from a file. This will read the file
 * and generate all of the necessary OpenStreetNodes and OpenStreetWays.
 *
 * AOpenStreetMap stores a list of FOpenStreetNode and FOpenStreetWay. It also
 * stores the Nodes in a QuadTree so that it is efficient to search for Nodes
 * within a given area of space.
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
    
    // How often the Map should check for a change in Drawing values and redraw if necessary
    // The value given is in seconds
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drawing)
    float RefreshRate;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Get MapProjection
    UFUNCTION(BlueprintPure, Category = Map)
    UMapProjectionComponent* GetProjection();
    
    // Generates a network of pink debug lines that draws the Nodes and Ways
    UFUNCTION(BlueprintNativeEvent, Category = Drawing)
    void DrawMap() const;

    // Find Nodes
    // Returns nullptr if no Node with given Id exists in the Map
    // TODO Add HasNodeWithId() function (same for Ways)
    const FOpenStreetNode* FindNodeById(int32 Id) const;

    // TODO Find Nodes near LatLng/Vector with given radius

    // Find Ways
    // Returns nullptr if no Node with given Id exists in the Map
    const FOpenStreetWay* FindWayById(int32 Id) const;

    // TODO Find Ways near LatLng/Vector with given radius
    
    // Checks to see if there has been a change in values
    // TODO Remove when we move DrawMap to the construction script
    void CheckForChangedDrawValues();

private:
    // The MapProjection used to convert Nodes' LatLng positions to 3D World coordinates
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    UMapProjectionComponent* Projection;

    // TODO Have a Quadtree of Nodes
    
    // Keep track of the previous values of Drawing parameters so we can see if they've changed
    float PrevRoadWidth;
    FColor PrevRoadColor;
    float PrevRefreshRate;
    float PrevDefaultHeight;
    float PrevScaleFactor;
    
    // Checks if values have changed since last refresh check
    bool ValuesHaveChanged() const;
};
