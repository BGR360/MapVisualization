// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "OpenStreetTag.h"
#include "OpenStreetElement.generated.h"

/**
 * Represents any Element in an OpenStreetMap. An Element is any object found in an OSM XML file.
 * Thus, AOpenStreetElement is the base for AOpenStreetNode and AOpenStreetWay.
 *
 * The thing that every type of Element has in common is a set of Tags. So AOpenStreetElement stores
 * a list of FOpenStreetTag.
 */
UCLASS()
class MAPVISUALIZATION_API AOpenStreetElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenStreetElement();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Get Tags
	TArray<FOpenStreetTag>* GetTags();

	// Add Tag
	void AddTag(FOpenStreetTag Tag);
	void AddTag(const FString& Key, const FString& Value);

	// Has Tag
	bool HasTag(const FString& Key) const;

	/**
	 * Returns the value associated with the given key.
	 * @param Key The key string that we want the value for.
	 * @return The key's value if a Tag exists with that particular key, otherwise nullptr.
	 */
	FString* const GetTagValue(const FString& Key) const;

private:
	// The list of Tags that describe this Element
	TArray<FOpenStreetTag> Tags;
};
