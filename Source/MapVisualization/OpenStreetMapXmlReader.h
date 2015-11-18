// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "OpenStreetMapModule/Public/LatLngBounds.h"
#include "OpenStreetMapModule/Public/OpenStreetNode.h"
#include "OpenStreetMapModule/Public/OpenStreetWay.h"
#include "OpenStreetMapModule/Public/OpenStreetTag.h"

/**
 * Reads an OSM XML file and populates an AOpenStreetMap actor with the proper
 * Nodes and Ways.
 */
class MAPVISUALIZATION_API OpenStreetMapXmlReader : public IFastXmlCallback
{
public:
    OpenStreetMapXmlReader();
    ~OpenStreetMapXmlReader();

    // Get/Set Map
    void SetMapActor(class AOpenStreetMap* Map);
    const AOpenStreetMap* GetMapActor() const;

    // Read from file
    // Does nothing if MapActor is null
    void ReadFromFile(const FString& FilePath);

    // Checks if in the process of reading
    bool IsReading() const;


    //------------------------------------
    // Inherited from IFastXmlCallback
    //------------------------------------

    virtual bool ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber);
    virtual bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber);
    virtual bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue);
    virtual bool ProcessClose(const TCHAR* Element);
    virtual bool ProcessComment(const TCHAR* Comment);

private:
    // The OpenStreetMap that this reader is going to populate
    AOpenStreetMap* MapActor;

    // Variables relating to the current state of the reader
    bool bReadingFile;
    bool bReadingBounds;
    bool bReadingTag;
    bool bReadingNode;
    bool bReadingWay;
    bool bReadingRelation;
    bool bReadingMember;

    // Keep track of the current object being created while reading an element
    // When the element ends, the object has all required fields filled in
    // So reset the object
    FOpenStreetNode CurrentNode;
    FOpenStreetWay CurrentWay;
    FOpenStreetTag CurrentTag;
    FLatLngBounds CurrentBounds;
    
    // The Ids for Nodes and ways can get really big, so lets minimize them
    // As much as possible. Blueprints can only handle int32's.
    // To do so, we'll keep track of the minimum.
    int64 MinNodeId;
    int64 MinWayId;
    int64 CurrentNodeId;
    int64 CurrentWayId;
    
    // We must keep track of the original int64 Ids ourselves before passing them on to AOpenStreetMap
    TMap<int64, FOpenStreetNode> Nodes;
    TMap<int64, FOpenStreetWay> Ways;
};
