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
struct OPENSTREETMAPMODULE_API FOpenStreetElement
{
    GENERATED_USTRUCT_BODY()

public:
    FOpenStreetElement();
    ~FOpenStreetElement();
    
    // The list of Tags that describe this Element
    TArray<FOpenStreetTag> Tags;
};
