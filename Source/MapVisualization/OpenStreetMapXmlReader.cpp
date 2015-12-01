// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMapXmlReader.h"
#include "MapProjectionComponent.h"
#include "OpenStreetMap.h"
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
CurrentNode(),
CurrentWay(),
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

    /* UE_LOG(Xml, Log, TEXT("Line %d: Begin element <%s>"),
        XmlFileLineNumber, ElementName); */

    
    // Check which element is beginning
    
    // <bounds> element
    if (ElementNameString == TEXT("bounds"))
    {
        bReadingBounds = true;
        
        // Construct a new FLatLngBounds
        CurrentBounds = FLatLngBounds();
    }
    
    // <node> element
    else if (ElementNameString == TEXT("node"))
    {
        bReadingNode = true;

        // Construct a new FOpenStreetNode
        CurrentNode = FOpenStreetNode();
        CurrentNodeId = -1;
    }
    
    // <way>
    //   <nd> element
    // </way>
    else if (ElementNameString == TEXT("nd"))
    {
        // Still reading a node, but it's a reference to a node inside of a way. Do not construct new node.
        bReadingNode = true;
    }
    
    // <tag> element
    else if (ElementNameString == TEXT("tag"))
    {
        bReadingTag = true;
        
        // Construct a new FOpenStreetTag
        CurrentTag = FOpenStreetTag();
    }
    
    // <way> element
    else if (ElementNameString == TEXT("way"))
    {
        bReadingWay = true;
        
        // Construct a new FOpenStreetWay
        CurrentWay = FOpenStreetWay();
        CurrentWayId = -1;
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
            if (AttributeNameString == TEXT("k"))
            {
                CurrentTag.Key = AttributeValue;
            }
            else if (AttributeNameString == TEXT("v"))
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
                    // Node Ids should have been reduced by this point
                    int64 BigNodeId = FCString::Atoi64(AttributeValue);
                    int32 SmallNodeId = MapActor->ToSmallerNodeId(BigNodeId);
                    const FOpenStreetNode* Node = MapActor->FindNodeById(SmallNodeId);
                    if (Node)
                    {
                        CurrentWay.Nodes.Add(*Node);
                    }
                }
            }

            // Else reading <node> attributes
            else
            {
                if (AttributeNameString == TEXT("id"))
                {
                    // Remember the Id of the Way so we can assign it later
                    int64 Id = FCString::Atoi64(AttributeValue);
                    CurrentNodeId = Id;
                }
                else if (AttributeNameString == TEXT("lat"))
                {
                    float Latitude = FCString::Atof(AttributeValue);
                    CurrentNode.Location.Latitude = Latitude;
                }
                else if (AttributeNameString == TEXT("lon"))
                {
                    float Longitude = FCString::Atof(AttributeValue);
                    CurrentNode.Location.Longitude = Longitude;
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
            if (AttributeNameString == TEXT("k"))
            {
                CurrentTag.Key = AttributeValue;
            }
            else if (AttributeNameString == TEXT("v"))
            {
                CurrentTag.Value = AttributeValue;
            }
        }
        
        // Else reading the <way> attributes
        else
        {
            // Set the Id of the Way
            if (AttributeNameString == TEXT("id"))
            {
                // Remember the Id of the Way so we can assign it later
                int64 Id = FCString::Atoi64(AttributeValue);
                CurrentWayId = Id;
            }
        }
    }

    return true;
}

bool OpenStreetMapXmlReader::ProcessClose(const TCHAR* Element)
{
    FString ElementNameString(Element);

    // UE_LOG(Xml, Log, TEXT("End element <%s>"), Element);

    // Check which element is ending
    
    if (ElementNameString == TEXT("bounds"))
    {
        bReadingBounds = false;
        
        // Set the bounds on the OpenStreetMap
        MapActor->GetProjection()->SetBounds(CurrentBounds);
    }
    else if (ElementNameString == TEXT("node"))
    {
        bReadingNode = false;
        
        // Add the Node to the map if its within the LatLngBounds
        if (MapActor->GetProjection()->IsInBounds(CurrentNode.Location))
        {
            MapActor->AddNode(CurrentNodeId, CurrentNode);
        }
    }
    else if (ElementNameString == TEXT("nd"))
    {
        bReadingNode = false;
    }
    else if (ElementNameString == TEXT("tag"))
    {
        bReadingTag = false;
        
        // Check which type of element we're supposed to add the Tag to
        if (bReadingWay)
        {
            CurrentWay.Tags.Add(CurrentTag);
        }
        else if (bReadingNode)
        {
            CurrentNode.Tags.Add(CurrentTag);
        }
    }
    else if (ElementNameString == TEXT("way"))
    {
        bReadingWay = false;
        
        // Check to see if it's a highway, and give it the proper values if so
        for (auto& Tag : CurrentWay.Tags)
        {
            // Check if it contains a "highway" tag
            if (Tag.Key == TEXT("highway"))
            {
                CurrentWay.bIsHighway = true;
            }
            
            // Check if has a "name" tag
            else if (Tag.Key == TEXT("name"))
            {
                
                CurrentWay.HighwayName = Tag.Value;
            }
            
            // Check if it has a "lanes" tag
            else if (Tag.Key == TEXT("lanes"))
            {
                int32 NumLanes = FCString::Atoi(*(Tag.Value));
                CurrentWay.NumLanes = NumLanes;
            }
        }
        
        // Get rid of the Way's HighwayName if it's not actually a highway
        if (!CurrentWay.bIsHighway)
        {
            CurrentWay.HighwayName = TEXT("");
        }
        
        // Store the Way in our int64 map until Ids have been reduced
        MapActor->AddWay(CurrentWayId, CurrentWay);
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
