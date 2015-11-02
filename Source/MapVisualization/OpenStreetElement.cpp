// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetElement.h"


// Sets default values
AOpenStreetElement::AOpenStreetElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AOpenStreetElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Get Tags
TArray<FOpenStreetTag>* AOpenStreetElement::GetTags()
{
	return nullptr;
}

// Add Tag
void AOpenStreetElement::AddTag(FOpenStreetTag Tag)
{

}

void AOpenStreetElement::AddTag(const FString& Key, const FString& Value)
{

}

// Has Tag
bool AOpenStreetElement::HasTag(const FString& Key) const
{
	return false;
}

// Get Tag Value
FString* const AOpenStreetElement::GetTagValue(const FString& Key) const
{
	return nullptr;
}
