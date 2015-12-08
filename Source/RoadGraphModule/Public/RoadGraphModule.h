// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(RoadGraphModule, All, All)

class OPENSTREETMAPMODULE_API FRoadGraphModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};