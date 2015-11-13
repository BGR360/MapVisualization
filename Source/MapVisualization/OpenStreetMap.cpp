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
        DrawDebugMap();
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

FOpenStreetNode* AOpenStreetMap::AddNode(FOpenStreetNode Node)
{
    return &(Nodes.Add(Node.Id, Node));
}

FOpenStreetNode* AOpenStreetMap::EmplaceNode(int64 Id, FLatLng Location)
{
    return &(Nodes.Add(Id, FOpenStreetNode(Id, Location)));
}

// Add Way
// Returns a pointer to the new Way in the list

FOpenStreetWay* AOpenStreetMap::AddWay(FOpenStreetWay Way)
{
    return &(Ways.Add(Way.Id, Way));
}

FOpenStreetWay* AOpenStreetMap::EmplaceWay(int64 Id)
{
    return &(Ways.Add(Id, FOpenStreetWay(Id)));
}

// Get Nodes/Ways

TMap<int64, FOpenStreetNode>* AOpenStreetMap::GetNodes()
{
    return &Nodes;
}

TMap<int64, FOpenStreetWay>* AOpenStreetMap::GetWays()
{
    return &Ways;
}

// Find Nodes
// Returns nullptr if no Node with given Id exists in the Map
FOpenStreetNode* AOpenStreetMap::FindNodeById(int64 Id)
{
    FOpenStreetNode* Node = Nodes.Find(Id);
    return Node;
}

// Find Ways
// Returns nullptr if no Node with given Id exists in the Map
FOpenStreetWay* AOpenStreetMap::FindWayById(int64 Id)
{
    FOpenStreetWay* Way = Ways.Find(Id);
    return Way;
}

// Generates a network of pink debug lines that draws the Nodes and Ways
void AOpenStreetMap::DrawDebugMap_Implementation() const
{
    // First clear all lines
    UWorld* World = GetWorld();
    if (World)
    {
        FlushPersistentDebugLines(World);
    }
    
    // Draw lines connecting its nodes
    for (auto& Element : Ways)
    {
        FOpenStreetWay CurrentWay = Element.Value;
        for (int32 j = 1; j < CurrentWay.Nodes.Num(); ++j)
        {
            FLatLng StartLatLng = CurrentWay.Nodes[j].Location;
            FLatLng EndLatLng = CurrentWay.Nodes[j - 1].Location;
            
            FVector Start = Projection->EarthToWorld(StartLatLng);
            FVector End = Projection->EarthToWorld(EndLatLng);
            
            if (World)
            {
                DrawDebugLine(
                              World,
                              Start,
                              End,
                              RoadColor,
                              true,
                              -1.0f,
                              255,
                              RoadWidth * Projection->ScaleFactor);
            }
        }
    }
}

// Checks to see if there has been a change in values
void AOpenStreetMap::CheckForChangedDrawValues()
{
    if (ValuesHaveChanged())
    {
        DrawDebugMap();
        
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
