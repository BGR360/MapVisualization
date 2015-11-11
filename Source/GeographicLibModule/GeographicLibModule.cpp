// Fill out your copyright notice in the Description page of Project Settings.

#include "GeographicLibModule.h"

IMPLEMENT_GAME_MODULE( FGeographicLibModule, GeographicLibModule );

DEFINE_LOG_CATEGORY(GeographicLibModule)

#define LOCTEXT_NAMESPACE "MyGameEditor"

void FGeographicLibModule::StartupModule()
{
    UE_LOG(GeographicLibModule, Warning, TEXT("GeographicLibModule: Log Started"));
}

void FGeographicLibModule::ShutdownModule()
{
    UE_LOG(GeographicLibModule, Warning, TEXT("GeographicLibModule: Log Ended"));
}

#undef LOCTEXT_NAMESPACE