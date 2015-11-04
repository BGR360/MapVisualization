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
    }
}

UMapProjectionComponent* AOpenStreetMap::GetProjection()
{
    return Projection;
}
