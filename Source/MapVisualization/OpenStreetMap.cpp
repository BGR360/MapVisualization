// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMap.h"
#include "OpenStreetMapXmlReader.h"
#include "MapProjectionComponent.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"


// Sets default values
AOpenStreetMap::AOpenStreetMap()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    Projection = CreateDefaultSubobject<UMapProjectionComponent>(TEXT("MapProjection"));
    RoadWidth = PrevRoadWidth = 1.0f;
    RoadColor = PrevRoadColor = FColor(255, 0, 255);
    RefreshRate = PrevRefreshRate = 2.0f;
    
    PrevDefaultHeight = Projection->DefaultHeight;
    PrevScaleFactor = Projection->ScaleFactor;

    NextNodeId = 0;
    NextWayId = 0;
}

// Called when the game starts or when spawned
void AOpenStreetMap::BeginPlay()
{
    Super::BeginPlay();

    // Read the XML file.
    OpenStreetMapXmlReader Reader;
    Reader.SetMapActor(this);

    // Prompt user for a file location using a native "Open File" dialog
    TArray<FString> OutFilenames;
    int32 OutFilterIndex;
    void* WindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
    FDesktopPlatformModule::Get()->OpenFileDialog(
        WindowHandle,
        TEXT("Choose an OSM XML File"),
        FPaths::GameDir(),
        TEXT(""),
        TEXT("XML Files|*.xml;*.osm"),
        EFileDialogFlags::None,
        OutFilenames,
        OutFilterIndex);

    if (OutFilenames.Num() > 0)
    {
        FString& FilePath = OutFilenames[0];
        Reader.ReadFromFile(FilePath);
        
        // Draw the map
        DrawMap();
    }
    
    // Start the refresh timer that checks if something needs to be redrawn.
    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AOpenStreetMap::CheckForChangedDrawValues, RefreshRate, true);
}

// Get MapProjection
UMapProjectionComponent* AOpenStreetMap::GetProjection()
{
    return Projection;
}

// Add Node
// Returns a pointer to the new Node in the list

FOpenStreetNode* AOpenStreetMap::AddNode(int64 LargeId, FOpenStreetNode Node)
{
    Node.Id = NextNodeId;
    LargeToSmallNodeIds.Add(LargeId, NextNodeId);
    NextNodeId++;

    int32 Index = Nodes.Add(Node);
    return &Nodes[Index];
}

// Add Way
// Returns a pointer to the new Way in the list

FOpenStreetWay* AOpenStreetMap::AddWay(int64 LargeId, FOpenStreetWay Way)
{
    Way.Id = NextWayId;
    LargeToSmallWayIds.Add(LargeId, NextWayId);
    NextWayId++;

    int32 Index = Ways.Add(Way);
    return &Ways[Index];
}

// Get Nodes/Ways

TArray<FOpenStreetNode>* AOpenStreetMap::GetNodes()
{
    return &Nodes;
}

TArray<FOpenStreetWay>* AOpenStreetMap::GetWays()
{
    return &Ways;
}

// Returns the smaller int32 Id equivalent to the given int64 Id from the .osm file
int32 AOpenStreetMap::ToSmallerNodeId(int64 LargeNodeId) const
{
    const int32* SmallNodeId = LargeToSmallNodeIds.Find(LargeNodeId);
    if (SmallNodeId)
    {
        return *SmallNodeId;
    }
    else
    {
        return -1;
    }
}

int32 AOpenStreetMap::ToSmallerWayId(int64 LargeWayId) const
{
    const int32* SmallWayId = LargeToSmallWayIds.Find(LargeWayId);
    if (SmallWayId)
    {
        return *SmallWayId;
    }
    else
    {
        return -1;
    }
}

// Find Nodes
// Returns nullptr if no Node with given Id exists in the Map
const FOpenStreetNode* AOpenStreetMap::FindNodeById(int32 Id) const
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
const FOpenStreetWay* AOpenStreetMap::FindWayById(int32 Id) const
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
    for (auto& Way : Ways)
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
