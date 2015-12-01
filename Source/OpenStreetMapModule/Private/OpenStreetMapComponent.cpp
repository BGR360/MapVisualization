// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapComponent.h"
#include "OpenStreetMapFile.h"


// Sets default values for this component's properties
UOpenStreetMapComponent::UOpenStreetMapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UOpenStreetMapComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Find Nodes
// Returns nullptr if no Node with given Id exists in the Map
const FOpenStreetNode* UOpenStreetMapComponent::FindNodeById(int32 Id) const
{
    // Since we are numbering the Ids like 0, 1, 2, etc...
    // The Nodes array should already be sorted. So we can do a binary search
    int32 Begin = 0;
    int32 End = Nodes.Num() - 1;
    while (End - Begin > 0)
    {
        int32 Guess = Begin + (End - Begin) / 2;
        int32 GuessId = Nodes[Guess].Id;
        if (Id < GuessId)
        {
            End = Guess;
        }
        else if (Id > GuessId)
        {
            Begin = Guess + 1;
        }
        else
        {
            return &Nodes[Guess];
        }
    }

    return nullptr;
}

// Find Ways
// Returns nullptr if no Node with given Id exists in the Map
const FOpenStreetWay* UOpenStreetMapComponent::FindWayById(int32 Id) const
{
    // Since we are numbering the Ids like 0, 1, 2, etc...
    // The Ways array should already be sorted. So we can do a binary search
    int32 Begin = 0;
    int32 End = Ways.Num() - 1;
    while (End - Begin > 0)
    {
        int32 Guess = Begin + (End - Begin) / 2;
        int32 GuessId = Ways[Guess].Id;
        if (Id < GuessId)
        {
            End = Guess;
        }
        else if (Id > GuessId)
        {
            Begin = Guess;
        }
        else
        {
            return &Ways[Guess];
        }
    }

    return nullptr;
}

