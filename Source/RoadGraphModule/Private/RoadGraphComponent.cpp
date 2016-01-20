// Fill out your copyright notice in the Description page of Project Settings.

#include "RoadGraphModule.h"
#include "RoadGraphComponent.h"
#include "RoadGraph.h"
#include "Intersection.h"
#include "RoadSegment.h"
#include "OpenStreetWay.h"
#include "OpenStreetNode.h"
#include "OpenStreetMapFile.h"


// Sets default values for this component's properties
URoadGraphComponent::URoadGraphComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

    RoadGraph = CreateDefaultSubobject<URoadGraph>(TEXT("URoadGraph"));
    if (!RoadGraph)
    {
        UE_LOG(RoadGraphModule, Warning, TEXT("NewObject<URoadGraph> returned nullptr!"));
    }
}

// Get/Set Osm Asset
UOpenStreetMapFile* URoadGraphComponent::GetOsmAsset()
{
    return OsmAsset;
}

void URoadGraphComponent::SetOsmAsset(UOpenStreetMapFile* NewOsmAsset)
{
    OsmAsset = NewOsmAsset;
}

// Generates the RoadGraph if a valid Osm Asset is present
void URoadGraphComponent::GenerateRoadGraph()
{
    if (OsmAsset)
    {
        /**
         * To generate a RoadGraph, this function traverses through the OsmAsset's Ways
         * and keeps track of which Nodes occur in which Ways. If a Node with a
         * particular Id is found in more than 1 Way, it is probably an Intersection
         * between those Ways.
         */

        // A Map of < NodeId -> ListOfWayIdsItOccursIn >
        TMap<int32, TArray<int> > NodeOccurrences;

        // Iterate through all Ways in the OsmAsset
        for (FOpenStreetWay Way : *(OsmAsset->GetWays()))
        {
            // Iterate through all of its Nodes and take note that they occur in this Way
            for (int32 NodeId : Way.Nodes)
            {
                if (NodeOccurrences.Contains(NodeId))
                {
                    // Mark another occurrence of this Node
                    NodeOccurrences[NodeId].Add(Way.Id);
                }
                else
                {
                    // Mark the first occurrence of this Node
                    TArray<int32> NewArray;
                    NewArray.Add(Way.Id);
                    NodeOccurrences.Add(NodeId, NewArray);
                }
            }
        }

        // Iterate through the Map we just created to identify Intersections
        for (auto& Pair : NodeOccurrences)
        {
            int32 NodeId = Pair.Key;
            int32 NumOccurrences = Pair.Value.Num();
            if (NumOccurrences > 1)
            {
                // Add an Intersection to the RoadGraph
                if (RoadGraph)
                {
                    FOpenStreetNode* Node = OsmAsset->FindNodeById(NodeId);
                    RoadGraph->AddIntersection(FIntersection(Node));
                }
                else
                {
                    UE_LOG(RoadGraphModule, Warning, TEXT("No URoadGraph to work with."));
                }
            }
        }

        UE_LOG(RoadGraphModule, Log, TEXT("Done Generating Graph."));
    }
}

