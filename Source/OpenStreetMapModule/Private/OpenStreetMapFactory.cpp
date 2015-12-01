// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapFactory.h"
#include "OpenStreetMapFile.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "OpenStreetMapXmlReader.h"

#define LOCTEXT_NAMESPACE "OpenStreetMapFactory"

UOpenStreetMapFactory::UOpenStreetMapFactory()
{
    // We don't anybody to create an empty OSM Asset. That's just weird
    bCreateNew = false;
    bText = true;

    // THIS LINE IS VERY IMPORTANT
    bEditorImport = true;

    SupportedClass = UOpenStreetMapFile::StaticClass();
    Formats.Add(TEXT("osm;OSM xml file"));
}

UOpenStreetMapFactory::~UOpenStreetMapFactory()
{

}

// Begin UFactory Interface

/** Imports the OpenStreetMapFile from the text of the .osm xml file. */
UObject* UOpenStreetMapFactory::FactoryCreateText(
    UClass* InClass,
    UObject* InParent,
    FName InName,
    EObjectFlags Flags,
    UObject* Context,
    const TCHAR* Type,
    const TCHAR*& Buffer,
    const TCHAR* BufferEnd,
    FFeedbackContext* Warn)
{
    FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Type);

    UObject* NewAsset = nullptr;

    // Attempt to load the xml file
    OpenStreetMapXmlReader Reader;
    UOpenStreetMapFile* MapAsset = NewObject<UOpenStreetMapFile>(InParent, InName, Flags);
    if (MapAsset)
    {
        Reader.SetMapAsset(MapAsset);

        // Convert buffer to an FString
        FString String;
        //const int32 BufferSize = BufferEnd - Buffer;
        //appBufferToString( String, Buffer, BufferSize );
        int32 NumChars = (BufferEnd - Buffer);
        TArray<TCHAR>& StringChars = String.GetCharArray();
        StringChars.AddUninitialized(NumChars + 1);
        FMemory::Memcpy(StringChars.GetData(), Buffer, NumChars*sizeof(TCHAR));
        StringChars.Last() = 0;

        Reader.ReadFromText(String);
        NewAsset = MapAsset;
    }

    FEditorDelegates::OnAssetPostImport.Broadcast(this, NewAsset);
    
    return NewAsset;
}

/** Returns whether or not the given class is supported by this factory. */
bool UOpenStreetMapFactory::DoesSupportClass(UClass* Class)
{
    return Class == UOpenStreetMapFile::StaticClass();
}

/** Returns true if this factory can deal with the file sent in. */
bool UOpenStreetMapFactory::FactoryCanImport(const FString& Filename)
{
    return FPaths::GetExtension(Filename, true) == TEXT(".osm");
}

/** Returns the name of the factory for menus */
FText UOpenStreetMapFactory::GetDisplayName() const
{
    return LOCTEXT("OpenStreetMapFactoryDescription", "OSM xml file");
}

// End UFactory Interface

#undef LOCTEXT_NAMESPACE
