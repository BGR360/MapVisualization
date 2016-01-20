// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Containers/Array.h"
#include "OpenStreetNode.h"
#include "Intersection.generated.h"

struct FOpenStreetNode;
class URoadSegment;

/**
 * An Intersection is where multiple RoadSegments meet.
 * Intersections have incoming and outgoing RoadSegments.
 */
UCLASS()
class ROADGRAPHMODULE_API UIntersection : public UObject
{
    GENERATED_BODY()

public:
    UIntersection();
    ~UIntersection();

    UFUNCTION(BlueprintPure, Category = RoadGraph)
    bool IsValid() const;

    UFUNCTION(BlueprintPure, Category = RoadGraph)
    FOpenStreetNode GetOsmNode() const;

    UFUNCTION(BlueprintPure, Category = RoadGraph)
    int32 NumIncoming() const;

    UFUNCTION(BlueprintPure, Category = RoadGraph)
    int32 NumOutgoing() const;

    UFUNCTION(BlueprintCallable, Category = RoadGraph)
    void AddIncoming(URoadSegment* NewIncoming);

    UFUNCTION(BlueprintCallable, Category = RoadGraph)
    void AddOutgoing(URoadSegment* NewOutgoing);

    UFUNCTION(BlueprintCallable, Category = RoadGraph)
    bool RemoveIncoming(URoadSegment* ToRemove);

    UFUNCTION(BlueprintCallable, Category = RoadGraph)
    bool RemoveOutgoing(URoadSegment* ToRemove);

    void SetOsmNode(FOpenStreetNode* NewNode);

    TArray<URoadSegment*>& GetIncoming();
    TArray<URoadSegment*>& GetOutgoing();

private:
    // One Intersection should be located at a single OpenStreetNode
    FOpenStreetNode* OsmNode;

    // The RoadSegments that enter the Intersection
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RoadGraph, meta = (AllowPrivateAccess = "true"))
    TArray<URoadSegment*> Incoming;

    // The RoadSegments that leave the Intersection
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RoadGraph, meta = (AllowPrivateAccess = "true"))
    TArray<URoadSegment*> Outgoing;
};
