// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OpenStreetWay.generated.h"

UCLASS()
class MAPVISUALIZATION_API AOpenStreetWay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenStreetWay();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// TODO: Stub out interface
};
