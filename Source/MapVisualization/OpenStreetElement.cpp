// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetElement.h"


// Sets default values
FOpenStreetElement::FOpenStreetElement()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void FOpenStreetElement::BeginPlay()
{
    Super::BeginPlay();

}

// Get Tags
TArray<FOpenStreetTag>& FOpenStreetElement::GetTags()
{
    return Tags;
}

// Add Tag
void FOpenStreetElement::AddTag(FOpenStreetTag Tag)
{
    Tags.Add(Tag);
}

void FOpenStreetElement::AddTag(const FString& Key, const FString& Value)
{
    Tags.Add(FOpenStreetTag(Key, Value));
}

// Has Tag
bool FOpenStreetElement::HasTag(const FString& Key) const
{
    for (int32 i = 0; i < Tags.Num(); i++)
    {
        if (Tags[i].Key == Key)
            return true;
    }
    return false;
}

// Has Tag - Outputs IndexOf
int32 FOpenStreetElement::IndexOfTag(const FString& Key) const
{
    int32 IndexOfTag = -1;
    for (int32 i = 0; i < Tags.Num(); i++)
    {
        if (Tags[i].Key == Key)
        {
            IndexOfTag = i;
            return true;
        }
    }
    return IndexOfTag;
}

// Get Tag Value
FString FOpenStreetElement::GetTagValue(const FString& Key) const
{
    // Check if a Tag with Key exists
    int32 IndexOfTag = this->IndexOfTag(Key);
    if (IndexOfTag != -1)
    {
        return Tags[IndexOfTag].Value;
    }
    else
    {
        return TEXT("");
    }
}
