// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMapXmlReader.h"
#include "MapProjectionComponent.h"
#include "OpenStreetMap.h"
#include "GeoComponent.h"
#include "OpenStreetWay.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"

#define LOCTEXT_NAMESPACE "Xml"
static const float DEBUG_POINT_SIZE = 3.5f;
static const float DEBUG_SPHERE_RADIUS = 10.f;
static const float DEBUG_LINE_THICKNESS = 1.5f;
static const int DEBUG_SPHERE_NUM_LINES = 4;
static const int DEBUG_SPHERE_DEPTH_PRIORITY = 255;
static const float DEBUG_POINT_HEIGHT = 30.f;
static const float DEBUG_LINE_HEIGHT = DEBUG_POINT_HEIGHT;
static const float DEBUG_POINT_LINES_SCALE_FACTOR = 7.f;

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

        // Draw a debug point at each Node
        // TODO Move to OpenStreetMap
        UWorld* World = MapActor->GetWorld();
        if (World)
        {
            for (auto& Element : NodeMap)
            {
                FOpenStreetNode* Node = Element.Value;

                if (Node)
                {
                    FLatLng LatLng = Node->GetGeoComponent()->GetLocation();
                    FVector Location = MapActor->GetProjection()->EarthToWorld(LatLng);
                    Location *= ::DEBUG_POINT_LINES_SCALE_FACTOR;
                    Location.Z = ::DEBUG_POINT_HEIGHT;

                    DrawDebugPoint(
                        World,
                        Location,
                        ::DEBUG_POINT_SIZE,
                        FColor(255, 0, 255),
                        true,
                        -1.0f,
                        ::DEBUG_SPHERE_DEPTH_PRIORITY);
                }
            }
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
        
        // Construct a new FLatLngBounds
        CurrentBounds = FLatLngBounds();
    }
    
    // <node> element
    else if (ElementNameString == TEXT("node"))
    {
        bReadingNode = true;

        // Construct a new FOpenStreetNode
        CurrentNode = FOpenStreetNode();
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
        CurrentTag = FOpenSTreetTag();
    }
    
    // <way> element
    else if (ElementNameString == TEXT("way"))
    {
        bReadingWay = true;
        
        // Construct a new FOpenStreetWay
        CurrentWay = FOpenSTreetWay();
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
                    FOpenStreetNode* Node = MapActor->FindNodeById(Id);
                    if (Node)
                    {
                        CurrentWay.AddNode(Node);
                    }
                }
            }

            // Else reading <node> attributes
            else
            {
                if (AttributeNameString == TEXT("id"))
                {
                    // Set the Id of the Node
                    int64 Id = FCString::Atoi64(AttributeValue);
                    CurrentNode.Id = Id;
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
        else
        {
            // Set the Id of the Way
            if (AttributeNameString == TEXT("id"))
            {
                // Set the Id of the Node
                int64 Id = FCString::Atoi64(AttributeValue);
                CurrentWay.Id = Id;
            }
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
    }
    else if (ElementNameString == TEXT("node"))
    {
        bReadingNode = false;
        
        // Add the Node to the map
        MapActor->AddNode(CurrentNode);
    }
    else if (ElementNameString == TEXT("nd"))
    {
        bReadingNode = false;
    }
    else if (ElementNameString == TEXT("tag"))
    {
        bReadingTag = false;
        
        // Check which type of element we're supposed to add the Tag to
        if (bReadingWay && CurrentWay != nullptr)
        {
            CurrentWay.AddTag(CurrentTag);
        }
        else if (bReadingNode && CurrentNode != nullptr)
        {
            CurrentNode.AddTag(CurrentTag);
        }
    }
    else if (ElementNameString == TEXT("way"))
    {
        bReadingWay = false;
        
        // Add the Way to the Map
        MapActor->AddWay(CurrentWay);

        // The Way is finished, draw lines connecting its nodes
        // TODO Move to OpenStreetMap
        if (CurrentWay)
        {
            TArray<FOpenStreetNode*>& Nodes = *(CurrentWay->GetNodes());
            for (int32 i = 1; i < Nodes.Num(); ++i)
            {
                FLatLng StartLatLng = Nodes[i]->GetGeoComponent()->GetLocation();
                FLatLng EndLatLng = Nodes[i - 1]->GetGeoComponent()->GetLocation();

                FVector Start = MapActor->GetProjection()->EarthToWorld(StartLatLng) * ::DEBUG_POINT_LINES_SCALE_FACTOR;
                FVector End = MapActor->GetProjection()->EarthToWorld(EndLatLng) * ::DEBUG_POINT_LINES_SCALE_FACTOR;
                Start.Z = ::DEBUG_LINE_HEIGHT;
                End.Z = ::DEBUG_LINE_HEIGHT;

                UWorld* World = MapActor->GetWorld();
                if (World)
                {
                    DrawDebugLine(
                        World,
                        Start,
                        End,
                        FColor(255, 0, 255),
                        true,
                        -1.0f,
                        ::DEBUG_SPHERE_DEPTH_PRIORITY,
                        ::DEBUG_LINE_THICKNESS);
                }
            }
        }
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
