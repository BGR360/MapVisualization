// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoadSegment.generated.h"

class UIntersection;

/**
 * A RoadSegment is a path between two intersections.
 * A RoadSegment is strictly one-way.
 */
UCLASS()
class ROADGRAPHMODULE_API URoadSegment : public UObject
{
    GENERATED_BODY()

public:
    URoadSegment();
    ~URoadSegment();

    UFUNCTION(BlueprintPure, Category = RoadGraph)
    bool IsValid() const;

    UFUNCTION(BlueprintPure, Category = RoadGraph)
    UIntersection* GetBegin() const;

    UFUNCTION(BlueprintPure, Category = RoadGraph)
    UIntersection* GetEnd() const;

    // When you set Begin/End, it updates the Outgoing/Incoming of the Intersections it belonged to and newly belongs to

    UFUNCTION(BlueprintCallable, Category = RoadGraph)
    void SetBegin(UIntersection* NewBegin);

    UFUNCTION(BlueprintCallable, Category = RoadGraph)
    void SetEnd(UIntersection* NewEnd);

private:
    UPROPERTY(VisibleAnywhere, Category = RoadGraph)
    UIntersection* Begin;

    UPROPERTY(VisibleAnywhere, Category = RoadGraph)
    UIntersection* End;
};
