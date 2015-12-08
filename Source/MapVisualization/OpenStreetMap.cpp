// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMap.h"
#include "OpenStreetMapXmlReader.h"
#include "MapProjectionComponent.h"
#include "OpenStreetMapModule/Public/OpenStreetMapComponent.h"
#include "OpenStreetMapModule/Public/OpenStreetMapFile.h"
#include "OpenStreetMapModule/Public/OpenStreetNode.h"
#include "OpenStreetMapModule/Public/OpenStreetWay.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"


// Sets default values
AOpenStreetMap::AOpenStreetMap()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    Projection = CreateDefaultSubobject<UMapProjectionComponent>(TEXT("MapProjection"));
    Map = CreateDefaultSubobject<UOpenStreetMapComponent>(TEXT("Map"));

    RoadWidth = 1.0f;
    DefaultWayColor = FColor(255, 0, 255);
    RoadColor = FColor(128, 255, 32);
}

// Called whenever the Construction Script is called (UPROPERTY changes, etc.)
void AOpenStreetMap::OnConstruction(const FTransform& Transform)
{
    if (Map)
    {
        if (Map->MapFile)
        {
            Projection->SetBounds(Map->MapFile->GetBounds());
            DrawMap();
        }
        else
        {
            // If we have deassigned the Map, erase all the debug lines
            EraseDebugLines();
        }
    }
}

// Called when the Actor is destroyed
void AOpenStreetMap::Destroyed()
{
    Super::Destroyed();

    // Clear all lines
    EraseDebugLines();
}

// Get MapProjection
UMapProjectionComponent* AOpenStreetMap::GetProjection()
{
    return Projection;
}

// Get MapComponent
UOpenStreetMapComponent* AOpenStreetMap::GetMap()
{
    return Map;
}

// Generates a network of pink debug lines that draws the Nodes and Ways
void AOpenStreetMap::DrawMap_Implementation() const
{
    UWorld* World = GetWorld();

    // First clear all lines
    EraseDebugLines();
    
    // Draw lines connecting its nodes
    for (auto& Way : *(Map->MapFile->GetWays()))
    {
        FColor Color = DefaultWayColor;
        float Width = RoadWidth;
        
        if (Way.bIsHighway)
        {
            Color = RoadColor;
            Width = RoadWidth * 2;
            
            if (Way.NumLanes > 0)
            {
                Width *= Way.NumLanes;
            }
        }
        
        for (int32 j = 1; j < Way.Nodes.Num(); ++j)
        {
            const FOpenStreetNode* StartNode = Map->MapFile->FindNodeById(Way.Nodes[j - 1]);
            const FOpenStreetNode* EndNode = Map->MapFile->FindNodeById(Way.Nodes[j]);

            if (StartNode && EndNode)
            {
                FLatLng StartLatLng = StartNode->Location;
                FLatLng EndLatLng = EndNode->Location;

                FVector Start = Projection->EarthToWorld(StartLatLng);
                FVector End = Projection->EarthToWorld(EndLatLng);

                if (World)
                {
                    DrawDebugLine(
                        World,
                        Start,
                        End,
                        Color,
                        true,
                        -1.0f,
                        255,
                        Width * Projection->ScaleFactor);
                }
            }
        }
    }
}

void AOpenStreetMap::EraseDebugLines() const
{
    UWorld* World = GetWorld();
    if (World)
    {
        FlushPersistentDebugLines(World);
    }
}
