// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapComponentBroker.h"
#include "OpenStreetMapFile.h"
#include "OpenStreetMapComponent.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"

// Begin ComponentAssetBroker Interface

/** Reports the asset class this broker knows how to handle */
UClass* FOpenStreetMapComponentBroker::GetSupportedAssetClass()
{
    return UOpenStreetMapFile::StaticClass();
}

/** Assign the assigned asset to the supplied component */
bool FOpenStreetMapComponentBroker::AssignAssetToComponent(UActorComponent* InComponent, UObject* InAsset)
{
    if (UOpenStreetMapComponent* OpenStreetMapComponent = Cast<UOpenStreetMapComponent>(InComponent))
    {
        UOpenStreetMapFile* OpenStreetMapAsset = Cast<UOpenStreetMapFile>(InAsset);

        if ((OpenStreetMapAsset != NULL) || (InAsset == NULL))
        {
            OpenStreetMapComponent->MapFile = OpenStreetMapAsset;
            return true;
        }
    }

    return false;
}

/** Get the currently assigned asset from the component */
UObject* FOpenStreetMapComponentBroker::GetAssetFromComponent(UActorComponent* InComponent)
{
    if (UOpenStreetMapComponent* OpenStreetMapComponent = Cast<UOpenStreetMapComponent>(InComponent))
    {
        return OpenStreetMapComponent->MapFile;
    }
    return NULL;
}

// End ComponentAssetBrokerInterface