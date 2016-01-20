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
    GENERATED_UCLASS_BODY()

    URoadSegment();
    ~URoadSegment();

    UFUNCTION(BlueprintPure)
    bool IsValid() const;

    UFUNCTION(BlueprintPure)
    UIntersection* GetBegin() const;

    UFUNCTION(BlueprintPure)
    UIntersection* GetEnd() const;

    // When you set Begin/End, it updates the Outgoing/Incoming of the Intersections it belonged to and newly belongs to

    UFUNCTION(BlueprintCallable)
    void SetBegin(UIntersection* NewBegin);

    UFUNCTION(BlueprintCallable)
    void SetEnd(UIntersection* NewEnd);

private:
    UPROPERTY(VisibleAnywhere)
    UIntersection* Begin;

    UPROPERTY(VisibleAnywhere)
    UIntersection* End;
};
