// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "OpenStreetMapComponentBroker.h"

DECLARE_LOG_CATEGORY_EXTERN(OpenStreetMapModule, All, All)

class OPENSTREETMAPMODULE_API FOpenStreetMapModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    // The ComponentAssetBroker that allows users to drag-n-drop OSM assets
    TSharedPtr<FOpenStreetMapComponentBroker> OpenStreetMapBroker;
};