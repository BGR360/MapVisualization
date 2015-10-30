// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "TestClass.h"

#include "GeoComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAPVISUALIZATION_API UGeoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeoComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTestClass MyTestClass;
};
