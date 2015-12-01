// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Editor/UnrealEd/Public/ComponentAssetBroker.h"

class UClass;
class UActorComponent;
class UObject;

/**
* This is what allows the OpenStreetMapFile Asset to be dragged from the Content Browser
* onto an OpenStreetMapComponent, just like you would do with a StaticMesh.
*/
class FOpenStreetMapComponentBroker : public IComponentAssetBroker
{
public:
    // Begin ComponentAssetBroker Interface

    /** Reports the asset class this broker knows how to handle */
    virtual UClass* GetSupportedAssetClass() override;

    /** Assign the assigned asset to the supplied component */
    virtual bool AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset) override;

    /** Get the currently assigned asset from the component */
    virtual UObject* GetAssetFromComponent(UActorComponent* InComponent) override;

    // End ComponentAssetBrokerInterface
};