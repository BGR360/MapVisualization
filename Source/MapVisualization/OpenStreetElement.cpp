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
	Tags.Add(Tag);
}

void AOpenStreetElement::AddTag(const FString& Key, const FString& Value)
{
	Tags.Add(FOpenStreetTag(Key, Value));
}

// Has Tag
bool AOpenStreetElement::HasTag(const FString& Key) const
{
	for (int32 i = 0; i < Tags.Num(); i++)
	{
		if (Tags[i].Key == Key)
			return true;
	}
	return false;
}

// Has Tag - Outputs IndexOf
bool AOpenStreetElement::HasTag(const FString& Key, int32& IndexOfTag) const
{
	for (int32 i = 0; i < Tags.Num(); i++)
	{
		if (Tags[i].Key == Key)
		{
			IndexOfTag = i;
			return true;
		}
	}
	IndexOfTag = -1;
	return false;
}

// Get Tag Value
const FString* AOpenStreetElement::GetTagValue(const FString& Key) const
{
	// Check if a Tag with Key exists
	int32 IndexOfTag;
	if (HasTag(Key, IndexOfTag))
	{
		const FString* Value = &(Tags[IndexOfTag].Value);
		return Value;
	}
	else
	{
		return nullptr;
	}
}
