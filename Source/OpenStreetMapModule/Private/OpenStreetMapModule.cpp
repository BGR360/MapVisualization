// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapComponent.h"
#include "Editor/UnrealEd/Public/ComponentAssetBroker.h"

IMPLEMENT_GAME_MODULE( FOpenStreetMapModule, OpenStreetMapModule );

DEFINE_LOG_CATEGORY(OpenStreetMapModule)

#define LOCTEXT_NAMESPACE "OpenStreetMapModule"

void FOpenStreetMapModule::StartupModule()
{
    UE_LOG(OpenStreetMapModule, Warning, TEXT("OpenStreetMapModule: Log Started"));

    // Register the OSM Asset's component broker
    UE_LOG(OpenStreetMapModule, Warning, TEXT("OpenStreetMapModule: Registering OSM Asset's ComponentAssetBroker..."));
    OpenStreetMapBroker = MakeShareable(new FOpenStreetMapComponentBroker);
    FComponentAssetBrokerage::RegisterBroker(OpenStreetMapBroker, UOpenStreetMapComponent::StaticClass(), true, true);
}

void FOpenStreetMapModule::ShutdownModule()
{
    UE_LOG(OpenStreetMapModule, Warning, TEXT("OpenStreetMapModule: Log Ended"));
}

#undef LOCTEXT_NAMESPACE