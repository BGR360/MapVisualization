// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenStreetMapComponent.generated.h"

/**
* Holds a reference to an OpenStreetMapFile Asset
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENSTREETMAPMODULE_API UOpenStreetMapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenStreetMapComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

    // The .osm file Asset
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
    class UOpenStreetMapFile* MapFile;
};
