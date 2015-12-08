// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct Intersection;

/**
 * A RoadSegment is a path between two intersections.
 * A RoadSegment is strictly one-way.
 */
struct ROADGRAPHMODULE_API RoadSegment
{
	RoadSegment();
	~RoadSegment();

    Intersection* Begin;
    Intersection* End;
};
