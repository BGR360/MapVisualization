// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetTag.h"

FOpenStreetTag::FOpenStreetTag() : Key(TEXT("")), Value(TEXT(""))
{
}

FOpenStreetTag::FOpenStreetTag(const FString& Key, const FString& Value) : Key(Key), Value(Value)
{
}

FOpenStreetTag::~FOpenStreetTag()
{
}
