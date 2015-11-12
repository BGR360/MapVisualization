// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "OpenStreetTag.h"
#include "OpenStreetElement.generated.h"

/**
 * Represents any Element in an OpenStreetMap. An Element is any object found in an OSM XML file.
 * Thus, AOpenStreetElement is the base for FOpenStreetNode and FOpenStreetWay.
 *
 * The thing that every type of Element has in common is a set of Tags. So FOpenStreetElement stores
 * a list of FOpenStreetTag.
 */
USTRUCT()
struct MAPVISUALIZATION_API FOpenStreetElement
{
    GENERATED_USTRUCT_BODY()

public:
    FOpenStreetElement();
    ~FOpenStreetElement();
    
    // The list of Tags that describe this Element
    TArray<FOpenStreetTag> Tags;

    // Add Tag
    //UFUNCTION(BlueprintCallable, Category = Map)
    void AddTag(const FString& Key, const FString& Value);

    // Has Tag
    //UFUNCTION(BlueprintPure, Category = Map)
    bool HasTag(const FString& Key) const;

    /**
     * Returns the index of the Tag with the given Key in Tags.
     * @param Key The Key string that we want to search for.
     * @param IndexOfTag Output parameter that gets the index of the found Tag (or -1 if not found)
     * @return The index of the first occurrence of such a Tag, or -1 if not found.
     */
    //UFUNCTION(BlueprintPure, Category = Map)
    int32 IndexOfTag(const FString& Key) const;

    /**
     * Returns the value associated with the given key.
     * @param Key The key string that we want the value for.
     * @return The key's value if a Tag exists with that particular key, otherwise nullptr.
     */
    //UFUNCTION(BlueprintCallable, Category = Map)
    FString GetTagValue(const FString& Key) const;
};
