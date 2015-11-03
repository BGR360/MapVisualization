// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMapXmlReader.h"

OpenStreetMapXmlReader::OpenStreetMapXmlReader() :
MapActor(nullptr),
bReadingBounds(false),
bReadingTag(false),
bReadingFile(false),
bReadingNode(false),
bReadingWay(false),
bReadingRelation(false),
bReadingMember(false)
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
		FFastXml::ParseXmlFile(this, *FilePath, nullptr, GWarn, true, true, OutErrorMessage, OutErrorLineNumber);
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

bool OpenStreetMapXmlReader::ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber)
{
	FString ElementDataString(ElementData);
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
	}
	else if (ElementNameString == "node" || ElementNameString == "nd")
	{
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
	return true;
}

bool OpenStreetMapXmlReader::ProcessClose(const TCHAR* Element)
{
	FString ElementNameString(Element);

	if (ElementNameString == "bounds")
	{
		bReadingBounds = false;
	}
	else if (ElementNameString == "node" || ElementNameString == "nd")
	{
		bReadingNode = false;
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
