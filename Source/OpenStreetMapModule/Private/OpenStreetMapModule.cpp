// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"

IMPLEMENT_GAME_MODULE( FOpenStreetMapModule, OpenStreetMapModule );

DEFINE_LOG_CATEGORY(OpenStreetMapModule)

#define LOCTEXT_NAMESPACE "OpenStreetMapModule"

void FOpenStreetMapModule::StartupModule()
{
    UE_LOG(OpenStreetMapModule, Warning, TEXT("OpenStreetMapModule: Log Started"));
}

void FOpenStreetMapModule::ShutdownModule()
{
    UE_LOG(OpenStreetMapModule, Warning, TEXT("OpenStreetMapModule: Log Ended"));
}

#undef LOCTEXT_NAMESPACE