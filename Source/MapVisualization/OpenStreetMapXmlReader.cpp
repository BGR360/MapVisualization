// Fill out your copyright notice in the Description page of Project Settings.

#include "MapVisualization.h"
#include "OpenStreetMapXmlReader.h"

OpenStreetMapXmlReader::OpenStreetMapXmlReader() :
MapActor(nullptr),
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
void OpenStreetMapXmlReader::ReadFromFile(const FString& FilePath)
{
	bReadingFile = true;

	// Pass the file to FFastXml
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
	return true;
}

bool OpenStreetMapXmlReader::ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber)
{
	return true;
}

bool OpenStreetMapXmlReader::ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue)
{
	return true;
}

bool OpenStreetMapXmlReader::ProcessClose(const TCHAR* Element)
{
	return true;
}

bool OpenStreetMapXmlReader::ProcessComment(const TCHAR* Comment)
{
	return true;
}
