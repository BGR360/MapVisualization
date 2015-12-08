// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "OpenStreetNode.h"
#include "OpenStreetWay.h"
#include "LatLng.h"
#include "LatLngBounds.h"
#include "OpenStreetMapFile.generated.h"

/**
 * This is an OpenStreetMap Asset. It is visible in the Content Browser and can be
 * dragged onto a UOpenStreetMapComponent.
 *
 * Contained in this Asset are all the data necessary to represent an OpenStreetMap:
 * Nodes and Ways
 */
UCLASS()
class OPENSTREETMAPMODULE_API UOpenStreetMapFile : public UObject
{
	GENERATED_BODY()
	
public:
    // Sets the default values
    UOpenStreetMapFile();
    virtual ~UOpenStreetMapFile();

    // Get/Set Bounds
    FLatLngBounds GetBounds() const;
    void SetBounds(FLatLngBounds Bounds);

    // Get Nodes/Ways
    TArray<FOpenStreetNode>* GetNodes();
    TArray<FOpenStreetWay>* GetWays();

    // Add Node
    // Returns a pointer to the new Node in the list
    FOpenStreetNode* AddNode(int64 LargeId, FOpenStreetNode Node);

    // Add Way
    // Returns a pointer to the new Way in the list
    FOpenStreetWay* AddWay(int64 LargeId, FOpenStreetWay Way);

    // Returns the smaller int32 Id equivalent to the given int64 Id from the .osm file
    int32 ToSmallerNodeId(int64 LargeNodeId) const;
    int32 ToSmallerWayId(int64 LargeWayId) const;

    // Find Nodes
    // Returns nullptr if no Node with given Id exists in the Map
    // TODO Add HasNodeWithId() function (same for Ways)
    const FOpenStreetNode* FindNodeById(int32 Id) const;

    // TODO Find Nodes near LatLng/Vector with given radius

    // Find Ways
    // Returns nullptr if no Node with given Id exists in the Map
    const FOpenStreetWay* FindWayById(int32 Id) const;

    // TODO Find Ways near LatLng/Vector with given radius

    // Get center of Bounds
    FLatLng GetBoundsCenter() const;

    // Check if a LatLng point is inside the Map's bounds
    bool IsInBounds(FLatLng Point) const;

private:
    // The bounding box of the map onto/from which we shall project
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    FLatLngBounds Bounds;

    // A list of all the Nodes on the map, ordered by Id
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    TArray<FOpenStreetNode> Nodes;

    // A list of all the Ways on the map, ordered by Id
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Map, meta = (AllowPrivateAccess = "true"))
    TArray<FOpenStreetWay> Ways;

    // The Ids of the Nodes/Ways in the .osm file require int64 storage due to their size, but Blueprints only support int32s
    // To remedy this, we store our own Id for each Node/Way (0, 1, 2, 3, etc.) because there are only so many nodes/ways in one map file.
    // This map stores the corresponding large Id (from the .osm file) to the smaller Id we use to communicate with the Blueprints
    TMap<int64, int32> LargeToSmallNodeIds;
    TMap<int64, int32> LargeToSmallWayIds;

    // These variables keep track of the next Ids we should assigne to a Node or a Way
    int32 NextNodeId;
    int32 NextWayId;
};
