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

    RoadWidth = PrevRoadWidth = 1.0f;
    RoadColor = PrevRoadColor = FColor(255, 0, 255);
    RefreshRate = PrevRefreshRate = 2.0f;
    
    PrevDefaultHeight = Projection->DefaultHeight;
    PrevScaleFactor = Projection->ScaleFactor;

    if (Map && Map->MapFile)
    {
        Projection->SetBounds(Map->MapFile->GetBounds());
    }
}

// Called when the game starts or when spawned
void AOpenStreetMap::BeginPlay()
{
    Super::BeginPlay();

    //// Read the XML file.
    //OpenStreetMapXmlReader Reader;

    //// Prompt user for a file location using a native "Open File" dialog
    //TArray<FString> OutFilenames;
    //int32 OutFilterIndex;
    //void* WindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
    //FDesktopPlatformModule::Get()->OpenFileDialog(
    //    WindowHandle,
    //    TEXT("Choose an OSM XML File"),
    //    FPaths::GameDir(),
    //    TEXT(""),
    //    TEXT("XML Files|*.xml;*.osm"),
    //    EFileDialogFlags::None,
    //    OutFilenames,
    //    OutFilterIndex);

    //if (OutFilenames.Num() > 0)
    //{
    //    FString& FilePath = OutFilenames[0];
    //    Reader.ReadFromFile(FilePath);
    //    
    //    // Draw the map
    //    DrawMap();
    //}
    //
    //// Start the refresh timer that checks if something needs to be redrawn.
    //FTimerHandle TimerHandle;
    //GetWorldTimerManager().SetTimer(TimerHandle, this, &AOpenStreetMap::CheckForChangedDrawValues, RefreshRate, true);
}

// Get MapProjection
UMapProjectionComponent* AOpenStreetMap::GetProjection()
{
    return Projection;
}

// Generates a network of pink debug lines that draws the Nodes and Ways
void AOpenStreetMap::DrawMap_Implementation() const
{
    // First clear all lines
    UWorld* World = GetWorld();
    if (World)
    {
        FlushPersistentDebugLines(World);
    }
    
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
            FLatLng StartLatLng = Way.Nodes[j].Location;
            FLatLng EndLatLng = Way.Nodes[j - 1].Location;
            
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

// Checks to see if there has been a change in values
void AOpenStreetMap::CheckForChangedDrawValues()
{
    if (ValuesHaveChanged())
    {
        DrawMap();
        
        // Reset the delay of the FTimer if need be
        if (PrevRefreshRate != RefreshRate)
        {
            FTimerHandle TimerHandle;
            GetWorldTimerManager().SetTimer(TimerHandle, this, &AOpenStreetMap::CheckForChangedDrawValues, RefreshRate, true);
        }
    }
    
    // Reset all the "previous" values
    PrevRoadWidth = RoadWidth;
    PrevRoadColor = RoadColor;
    PrevRefreshRate = RefreshRate;
    PrevDefaultHeight = Projection->DefaultHeight;
    PrevScaleFactor = Projection->ScaleFactor;
}

// Checks if values have changed since last refresh check
bool AOpenStreetMap::ValuesHaveChanged() const
{
    return (PrevRoadWidth != RoadWidth) ||
    (PrevRoadColor != RoadColor) ||
    (PrevRefreshRate != RefreshRate) ||
    (PrevDefaultHeight != Projection->DefaultHeight) ||
    (PrevScaleFactor != Projection->ScaleFactor);
}
