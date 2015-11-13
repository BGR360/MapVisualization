// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "OpenStreetTag.generated.h"

/**
 * Represents a Tag in an OpenStreetMap Element. A Tag is simply a key and value pair,
 * such as {"highway", "motorway"}
 */
USTRUCT()
struct OPENSTREETMAPMODULE_API FOpenStreetTag
{
    GENERATED_USTRUCT_BODY()

    FOpenStreetTag();
    FOpenStreetTag(const FString& Key, const FString& Value);
    ~FOpenStreetTag();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map)
    FString Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map)
    FString Value;
};
