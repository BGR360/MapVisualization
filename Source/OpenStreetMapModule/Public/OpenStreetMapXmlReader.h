// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/XmlParser/Public/FastXml.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "LatLngBounds.h"
#include "OpenStreetNode.h"
#include "OpenStreetWay.h"
#include "OpenStreetTag.h"

/**
 * Reads an OSM XML file and populates an AOpenStreetMap actor with the proper
 * Nodes and Ways.
 */
class OPENSTREETMAPMODULE_API OpenStreetMapXmlReader : public IFastXmlCallback
{
public:
    OpenStreetMapXmlReader();
    ~OpenStreetMapXmlReader();

    // Get/Set Map
    void SetMapAsset(class UOpenStreetMapFile* Map);
    const UOpenStreetMapFile* GetMapAsset() const;

    // Read from file
    // Does nothing if MapActor is null
    void ReadFromFile(const FString& FilePath, FFeedbackContext* FeedbackContext = nullptr);

    // Read from text
    void ReadFromText(TCHAR* Text, FFeedbackContext* FeedbackContext = nullptr);

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
    UOpenStreetMapFile* MapAsset;

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
    
    // The Ids for Nodes and Ways are int32s in most of our code, but they are
    // int64s in the .osm file. The AOpenStreetMap actor will handle the conversion,
    // so we just need to keep track of what the current Node/Way's large int64 Id is.
    int64 CurrentNodeId;
    int64 CurrentWayId;
};
