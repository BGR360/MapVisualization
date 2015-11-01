// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetWay.h"


// Sets default values
AOpenStreetWay::AOpenStreetWay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOpenStreetWay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpenStreetWay::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

