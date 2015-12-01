// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenStreetMapModule.h"
#include "OpenStreetMapFactory.h"

UOpenStreetMapFactory::UOpenStreetMapFactory()
{
    // We don't anybody to create an empty OSM Asset. That's just weird
    bCreateNew = false;
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
    return nullptr;
}

/** Returns whether or not the given class is supported by this factory. */
bool UOpenStreetMapFactory::DoesSupportClass(UClass* Class)
{
    return false;
}

/** Returns true if this factory can deal with the file sent in. */
bool UOpenStreetMapFactory::FactoryCanImport(const FString& Filename)
{
    return false;
}

/** Returns the name of the factory for menus */
FText UOpenStreetMapFactory::GetDisplayName() const
{
    return FText();
}

// End UFactory Interface
