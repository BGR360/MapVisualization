// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Containers/Array.h"
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
    GENERATED_USTRUCT_BODY()

    UIntersection();
    ~UIntersection();

    UFUNCTION(BlueprintPure)
    bool IsValid() const;

    UFUNCTION(BlueprintPure)
    FOpenStreetNode GetOsmNode() const;

    UFUNCTION(BlueprintPure)
    int32 NumIncoming() const;

    UFUNCTION(BlueprintPure)
    int32 NumOutgoing() const;

    UFUNCTION(BlueprintCallable)
    void AddIncoming(URoadSegment* NewIncoming);

    UFUNCTION(BlueprintCallable)
    void AddOutgoing(URoadSegment* NewOutgoing);

    UFUNCTION(BlueprintCallable)
    bool RemoveIncoming(URoadSegment* ToRemove);

    UFUNCTION(BlueprintCallable)
    bool RemoveOutgoing(URoadSegment* ToRemove);

    TArray<URoadSegment*>& GetIncoming();
    TArray<URoadSegment*>& GetOutgoing();

private:
    // One Intersection should be located at a single OpenStreetNode
    FOpenStreetNode* OsmNode;

    // The RoadSegments that enter the Intersection
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = ("AllowPrivateAccess = true"))
    TArray<URoadSegment*> Incoming;

    // The RoadSegments that leave the Intersection
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = ("AllowPrivateAccess = true"))
    TArray<URoadSegment*> Outgoing;
};
