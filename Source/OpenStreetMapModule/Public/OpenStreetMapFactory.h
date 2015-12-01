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

};
