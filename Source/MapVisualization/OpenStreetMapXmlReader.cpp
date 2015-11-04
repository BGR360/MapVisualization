// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMapXmlReader.h"
#include "MapProjectionComponent.h"
#include "OpenStreetMap.h"
#include "OpenStreetNode.h"
#include "GeoComponent.h"
#include "OpenStreetWay.h"
#include "OpenStreetTag.h"
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
CurrentTag(nullptr)
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

    FString ElementNameString(ElementName);
    UE_LOG(Xml, Log, TEXT("Line %d: Begin element <%s>"),
        XmlFileLineNumber, ElementName);

    if (ElementNameString == "bounds")
    {
        bReadingBounds = true;
        // Reset CurrentBounds just in case
        CurrentBounds = FLatLngBounds();
    }
    else if (ElementNameString == "node")
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
    else if (ElementNameString == "nd")
    {
        // Still reading a node, but it's a reference to a node inside of a way. Do not spawn new node.
        bReadingNode = true;
    }
    else if (ElementNameString == "tag")
    {
        bReadingTag = true;
    }
    else if (ElementNameString == "way")
    {
        bReadingWay = true;
    }
    else if (ElementNameString == "relation")
    {
        bReadingRelation = true;
    }
    else if (ElementNameString == "member")
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
        if (AttributeNameString == "minlat")
        {
            CurrentBounds.LowerLeft.Latitude = FCString::Atof(AttributeValue);
        }
        else if (AttributeNameString == "minlon")
        {
            CurrentBounds.LowerLeft.Longitude = FCString::Atof(AttributeValue);
        }
        else if (AttributeNameString == "maxlat")
        {
            CurrentBounds.UpperRight.Latitude = FCString::Atof(AttributeValue);
        }
        else if (AttributeNameString == "maxlon")
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

        }

        // Else reading <node> or <nd> attributes
        else
        {
            // If reading <nd> attributes
            if (bReadingWay)
            {

            }

            // Else reading <node> attributes
            else if (CurrentNode != nullptr)
            {
                if (AttributeNameString == "id")
                {
                    int32 Id = FCString::Atoi(AttributeValue);
                    CurrentNode->SetId(Id);
                    // Now that we have the Id, add the Node to the NodeMap
                    NodeMap.Add(Id, CurrentNode);
                }
                else if (AttributeNameString == "lat")
                {
                    float Latitude = FCString::Atof(AttributeValue);
                    CurrentNode->GetGeoComponent()->GetLocation().Latitude = Latitude;
                }
                else if (AttributeNameString == "lon")
                {
                    float Longitude = FCString::Atof(AttributeValue);
                    CurrentNode->GetGeoComponent()->GetLocation().Longitude = Longitude;
                }

                // TODO Set the Projection of the Node's GeoComponent
            }
        }
    }

    return true;
}

bool OpenStreetMapXmlReader::ProcessClose(const TCHAR* Element)
{
    FString ElementNameString(Element);
    UE_LOG(Xml, Log, TEXT("End element <%s>"), Element);

    if (ElementNameString == "bounds")
    {
        bReadingBounds = false;
        // Set the bounds on the OpenStreetMap
        MapActor->GetProjection()->SetBounds(CurrentBounds);
        CurrentBounds = FLatLngBounds();
    }
    else if (ElementNameString == "node" || ElementNameString == "nd")
    {
        bReadingNode = false;
        CurrentNode = nullptr;
    }
    else if (ElementNameString == "tag")
    {
        bReadingTag = false;
    }
    else if (ElementNameString == "way")
    {
        bReadingWay = false;
    }
    else if (ElementNameString == "relation")
    {
        bReadingRelation = false;
    }
    else if (ElementNameString == "member")
    {
        bReadingMember = false;
    }
    else if (ElementNameString == "osm")
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
