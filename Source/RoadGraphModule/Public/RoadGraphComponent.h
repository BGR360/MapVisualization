// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "RoadGraphComponent.generated.h"

class URoadGraph;
class UOpenStreetMapFile;

/**
* The RoadGraphComponent holds a pointer to a FRoadGraph and is responsible
* for generating the RoadGraph from an OSM file.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROADGRAPHMODULE_API URoadGraphComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URoadGraphComponent();

    // Get/Set Osm Asset
    UOpenStreetMapFile* GetOsmAsset();
    void SetOsmAsset(UOpenStreetMapFile* NewOsmAsset);

    // Generates the RoadGraph if a valid Osm Asset is present
    void GenerateRoadGraph();
	
private:
    // The RoadGraph represented by this component. Will be generated when assigned an OSM Asset
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    URoadGraph* RoadGraph;

    // The OSM Asset that will supply the data necessary to generate the RoadGraph
    UPROPERTY()
    UOpenStreetMapFile* OsmAsset;
};
