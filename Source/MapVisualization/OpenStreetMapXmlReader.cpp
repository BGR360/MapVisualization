// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMapXmlReader.h"
#include "MapProjectionComponent.h"
#include "OpenStreetMap.h"
#include "OpenStreetNode.h"
#include "GeoComponent.h"
#include "OpenStreetWay.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"

#define LOCTEXT_NAMESPACE "Xml"

OpenStreetMapXmlReader::OpenStreetMapXmlReader() :
MapActor(nullptr),
bReadingBounds(false),
bReadingTag(false),
bReadingFile(false),
bReadingNode(false),
bReadingWay(false),
bReadingRelation(false),
bReadingMember(false),
CurrentNode(nullptr),
CurrentWay(nullptr),
CurrentTag()
{
}

OpenStreetMapXmlReader::~OpenStreetMapXmlReader()
{
}

// Get/Set Map

void OpenStreetMapXmlReader::SetMapActor(class AOpenStreetMap* Map)
{
    MapActor = Map;
}

const AOpenStreetMap* OpenStreetMapXmlReader::GetMapActor() const
{
    return MapActor;
}

// Read from file
// Do nothing if MapActor is null
void OpenStreetMapXmlReader::ReadFromFile(const FString& FilePath)
{
    bReadingFile = true;

    // Check to make sure MapActor is not null
    if (MapActor)
    {
        // Pass the file to FFastXml
        FText OutErrorMessage;
        int32 OutErrorLineNumber;
        FFeedbackContext* FeedbackContext = FDesktopPlatformModule::Get()->GetNativeFeedbackContext();
        FFastXml::ParseXmlFile(this, *FilePath, nullptr, FeedbackContext, true, true, OutErrorMessage, OutErrorLineNumber);

        // Check for errors opening the file
        if (!OutErrorMessage.IsEmpty())
        {
            FText DialogTitle = LOCTEXT("ErrorDialogTitle", "Error");
            FMessageDialog::Open(EAppMsgType::Ok, OutErrorMessage, &DialogTitle);
        }
    }
}

// Checks if in the process of reading
bool OpenStreetMapXmlReader::IsReading() const
{
    return bReadingFile;
}

//------------------------------------
// Inherited from IFastXmlCallback
//------------------------------------

// We don't need to do anything with the <osm> tag
bool OpenStreetMapXmlReader::ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber)
{
    return true;
}

/**
* There are 9 different possible situations that we could be in while reading an OSM XML file:
* 1) Reading <bounds> element:				bReadingBounds = true;
* 2) Reading <node> element:				bReadingNode = true
* 3) Reading <tag> inside <node>:			bReadingNode = true && bReadingTag = true
* 4) Reading <way> element:					bReadingWay = true
* 5) Reading <nd> inside <way>:				bReadingWay = true && bReadingNode = true
* 6) Reading <tag> inside <way>:			bReadingWay = true && bReadingTag = true
* 7) Reading <relation> element:			bReadingRelation = true
* 8) Reading <member> inside <relation>:	bReadingRelation = true && bReadingMember = true
* 9) Reading <tag> inside <relation>:		bReadingRelation = true && bReadingTag = true
*/

// Called when an element begins
bool OpenStreetMapXmlReader::ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber)
{
    // OSM doesn't store any data inside of elements, only inside of attributes, so we don't care about ElementData

    // Convert TCHAR* to FString
    FString ElementNameString(ElementName);
    UE_LOG(Xml, Log, TEXT("Line %d: Begin element <%s>"),
        XmlFileLineNumber, ElementName);

    // Check which element is beginning
    
    // <bounds> element
    if (ElementNameString == TEXT("bounds"))
    {
        bReadingBounds = true;
        // Reset CurrentBounds just in case
        CurrentBounds = FLatLngBounds();
    }
    
    // <node> element
    else if (ElementNameString == TEXT("node"))
    {
        bReadingNode = true;

        // Spawn new AOpenStreetNode and attach it to the AOpenStreetMap's RootComponent

        UWorld* World = MapActor->GetWorld();
        if (World)
        {
            FActorSpawnParameters Params;
            CurrentNode = World->SpawnActor<AOpenStreetNode>();
            if (CurrentNode)
            {
                // Attach to actor
                CurrentNode->AttachRootComponentToActor(MapActor);
            }
        }
    }
    
    // <way>
    //   <nd> element
    // </way>
    else if (ElementNameString == TEXT("nd"))
    {
        // Still reading a node, but it's a reference to a node inside of a way. Do not spawn new node.
        bReadingNode = true;
    }
    
    // <tag> element
    else if (ElementNameString == TEXT("tag"))
    {
        bReadingTag = true;
    }
    
    // <way> element
    else if (ElementNameString == TEXT("way"))
    {
        bReadingWay = true;
        
        // Spawn new AOpenStreetNode and attach it to the AOpenStreetMap's RootComponent
        
        UWorld* World = MapActor->GetWorld();
        if (World)
        {
            FActorSpawnParameters Params;
            CurrentWay = World->SpawnActor<AOpenStreetWay>();
            if (CurrentWay)
            {
                // Attach to actor
                CurrentWay->AttachRootComponentToActor(MapActor);
            }
        }
    }
    
    // <relation> element
    else if (ElementNameString == TEXT("relation"))
    {
        bReadingRelation = true;
    }
    
    // <relation>
    //   <member> element
    // </relation>
    else if (ElementNameString == TEXT("member"))
    {
        bReadingMember = true;
    }

    return true;
}

bool OpenStreetMapXmlReader::ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{
    FString AttributeNameString(AttributeName);

    // If inside <bounds> element
    if (bReadingBounds)
    {
        // Read the max and min LatLng values
        if (AttributeNameString == TEXT("minlat"))
        {
            CurrentBounds.LowerLeft.Latitude = FCString::Atof(AttributeValue);
        }
        else if (AttributeNameString == TEXT("minlon"))
        {
            CurrentBounds.LowerLeft.Longitude = FCString::Atof(AttributeValue);
        }
        else if (AttributeNameString == TEXT("maxlat"))
        {
            CurrentBounds.UpperRight.Latitude = FCString::Atof(AttributeValue);
        }
        else if (AttributeNameString == TEXT("maxlon"))
        {
            CurrentBounds.UpperRight.Longitude = FCString::Atof(AttributeValue);
        }
    }

    // If inside <node> element
    else if (bReadingNode)
    {
        // If inside <tag> element
        if (bReadingTag)
        {
            // Check if "key" or "value"
            if (AttributeNameString == TEXT("key"))
            {
                CurrentTag.Key = AttributeValue;
            }
            else if (AttributeNameString == TEXT("value"))
            {
                CurrentTag.Value = AttributeValue;
            }
        }

        // Else reading <node> or <nd> attributes
        else
        {
            // If reading <nd> attributes
            if (bReadingWay)
            {
                // Check for "ref" attribute
                if (AttributeNameString == TEXT("ref"))
                {
                    // Add node to CurrentWay
                    int64 Id = FCString::Atoi64(AttributeValue);
                    AOpenStreetNode* Node = NodeMap[Id];
                    if (Node)
                    {
                        CurrentWay->AddNode(Node);
                    }
                }
            }

            // Else reading <node> attributes
            else if (CurrentNode != nullptr)
            {
                if (AttributeNameString == TEXT("id"))
                {
                    // Set the Id of the Node
                    int64 Id = FCString::Atoi64(AttributeValue);
                    CurrentNode->SetId(Id);
                    // Now that we have the Id, add the Node to the NodeMap
                    NodeMap.Add(Id, CurrentNode);
                }
                else if (AttributeNameString == TEXT("lat"))
                {
                    float Latitude = FCString::Atof(AttributeValue);
                    CurrentNode->GetGeoComponent()->GetLocation().Latitude = Latitude;
                }
                else if (AttributeNameString == TEXT("lon"))
                {
                    float Longitude = FCString::Atof(AttributeValue);
                    CurrentNode->GetGeoComponent()->GetLocation().Longitude = Longitude;
                }
            }
        }
    }
    
    // If inside <way> element
    else if (bReadingWay)
    {
        // If inside <tag> element
        if (bReadingTag)
        {
            // Check if "key" or "value"
            if (AttributeNameString == TEXT("key"))
            {
                CurrentTag.Key = AttributeValue;
            }
            else if (AttributeNameString == TEXT("value"))
            {
                CurrentTag.Value = AttributeValue;
            }
        }
        
        // Else reading the <way> attributes
        else if (CurrentWay != nullptr)
        {
            // TODO Set the Id of the Way
        }
    }

    return true;
}

bool OpenStreetMapXmlReader::ProcessClose(const TCHAR* Element)
{
    FString ElementNameString(Element);
    UE_LOG(Xml, Log, TEXT("End element <%s>"), Element);

    // Check which element is ending
    
    if (ElementNameString == TEXT("bounds"))
    {
        bReadingBounds = false;
        // Set the bounds on the OpenStreetMap
        MapActor->GetProjection()->SetBounds(CurrentBounds);
        CurrentBounds = FLatLngBounds();
    }
    else if (ElementNameString == TEXT("node") || ElementNameString == TEXT("nd"))
    {
        bReadingNode = false;
        CurrentNode = nullptr;
    }
    else if (ElementNameString == TEXT("tag"))
    {
        bReadingTag = false;
        
        // Check which type of element we're supposed to add the Tag to
        if (bReadingWay && CurrentWay != nullptr)
        {
            CurrentWay->AddTag(CurrentTag);
        }
        else if (bReadingNode && CurrentNode != nullptr)
        {
            CurrentNode->AddTag(CurrentTag);
        }
        
        CurrentTag = FOpenStreetTag();
    }
    else if (ElementNameString == TEXT("way"))
    {
        bReadingWay = false;
        CurrentWay = nullptr;
    }
    else if (ElementNameString == TEXT("relation"))
    {
        bReadingRelation = false;
    }
    else if (ElementNameString == TEXT("member"))
    {
        bReadingMember = false;
    }
    else if (ElementNameString == TEXT("osm"))
    {
        bReadingFile = false;
    }

    return true;
}

// We don't care about comments
bool OpenStreetMapXmlReader::ProcessComment(const TCHAR* Comment)
{
    return true;
}

#undef LOCTEXT_NAMESPACE
