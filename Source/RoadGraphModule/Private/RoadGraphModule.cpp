// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"

IMPLEMENT_GAME_MODULE( FRoadGraphModule, RoadGraphModule );

DEFINE_LOG_CATEGORY(RoadGraphModule)

#define LOCTEXT_NAMESPACE "RoadGraphModule"

void FRoadGraphModule::StartupModule()
{
    UE_LOG(RoadGraphModule, Warning, TEXT("RoadGraphModule: Log Started"));
}

void FRoadGraphModule::ShutdownModule()
{
    UE_LOG(RoadGraphModule, Warning, TEXT("RoadGraphModule: Log Ended"));
}

#undef LOCTEXT_NAMESPACE