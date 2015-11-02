// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetWay.h"
#include "OpenStreetNode.h"


// Sets default values
AOpenStreetWay::AOpenStreetWay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AOpenStreetWay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Add Node
void AOpenStreetWay::AddNode(class AOpenStreetNode* Node)
{
    Nodes.Push(Node);
}

// Remove Node
int32 AOpenStreetWay::RemoveNode(AOpenStreetNode* Node)
{
    return Nodes.Remove(Node);
}

// Get Nodes
TArray<AOpenStreetNode*>* AOpenStreetWay::GetNodes()
{
    return &Nodes;
}
