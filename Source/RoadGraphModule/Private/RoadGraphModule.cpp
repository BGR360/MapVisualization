// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"

IMPLEMENT_GAME_MODULE( FRoadGraphModule, RoadGraphModule );

DEFINE_LOG_CATEGORY(RoadGraphModule)

#define LOCTEXT_NAMESPACE "RoadGraphModule"

void FOpenStreetMapModule::StartupModule()
{
    UE_LOG(OpenStreetMapModule, Warning, TEXT("RoadGraphModule: Log Started"));
}

void FOpenStreetMapModule::ShutdownModule()
{
    UE_LOG(OpenStreetMapModule, Warning, TEXT("RoadGraphModule: Log Ended"));
}

#undef LOCTEXT_NAMESPACE