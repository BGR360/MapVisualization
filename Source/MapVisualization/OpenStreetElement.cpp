// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetElement.h"


// Sets default values
AOpenStreetElement::AOpenStreetElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOpenStreetElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpenStreetElement::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

