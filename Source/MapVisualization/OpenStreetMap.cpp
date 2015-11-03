// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMap.h"
#include "OpenStreetMapXmlReader.h"


// Sets default values
AOpenStreetMap::AOpenStreetMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AOpenStreetMap::BeginPlay()
{
	Super::BeginPlay();
	
	// Read the XML file.
	OpenStreetMapXmlReader Reader;
	Reader.SetMapActor(this);
	Reader.ReadFromFile("map.osm");
}
