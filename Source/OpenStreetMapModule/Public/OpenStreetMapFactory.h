// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Factories/Factory.h"
#include "OpenStreetMapFactory.generated.h"

/**
 * This is what allows UOpenStreetMapFile to be an Asset in the Content Browser.
 * The Factory is responsible for importing the Asset from the .osm xml file.
 */
UCLASS()
class OPENSTREETMAPMODULE_API UOpenStreetMapFactory : public UFactory
{
	GENERATED_BODY()
	
public:
    UOpenStreetMapFactory();
    virtual ~UOpenStreetMapFactory();

    // Begin UFactory Interface

    /** Imports the OpenStreetMapFile from the text of the .osm xml file. */
    virtual UObject* FactoryCreateText(
        UClass* InClass,
        UObject* InParent,
        FName InName,
        EObjectFlags Flags,
        UObject* Context,
        const TCHAR* Type,
        const TCHAR*& Buffer,
        const TCHAR* BufferEnd,
        FFeedbackContext* Warn) override;

    /** Returns whether or not the given class is supported by this factory. */
    virtual bool DoesSupportClass(UClass* Class) override;

    /** Returns true if this factory can deal with the file sent in. */
    virtual bool FactoryCanImport(const FString& Filename) override;

    /** Returns the name of the factory for menus */
    virtual FText GetDisplayName() const override;

    // End UFactory Interface
};
