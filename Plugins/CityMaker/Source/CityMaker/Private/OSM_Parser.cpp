// Fill out your copyright notice in the Description page of Project Settings.

#include "OSM_Parser.h"

#include "XmlNode.h"
#include "XmlFile.h"

DEFINE_LOG_CATEGORY_STATIC(LogOSMParser, Log, Log)

#define EARTH_RADIUS 6373.0

double LatLonDistance(double Lat1, double Lon1, double Lat2, double Lon2)
{
	Lat1 = FMath::DegreesToRadians(Lat1);
	Lat2 = FMath::DegreesToRadians(Lat2);
	Lon1 = FMath::DegreesToRadians(Lon1);
	Lon2 = FMath::DegreesToRadians(Lon2);

	double dlat = Lat2 - Lat1;
	double dlon = Lon2 - Lon1;

	double a = FMath::Pow(FMath::Sin(dlat / 2), 2) + FMath::Cos(Lat1) * FMath::Cos(Lat2) * FMath::Pow(FMath::Sin(dlon / 2), 2);
	double c = 2 * FMath::Atan2(FMath::Sqrt(a), FMath::Sqrt(1 - a));

	return c * EARTH_RADIUS * 1000 * 100;
}

struct FLatLonCoordinate
{
	FLatLonCoordinate()
	{
	}

	void Fill(double InMinLat, double InMaxLat, double InMinLon, double InMaxLon)
	{
		MinLat = InMinLat;
		MaxLat = InMaxLat;
		MinLon = InMinLon;
		MaxLon = InMaxLon;

		Length = LatLonDistance(MinLat, MinLon, MaxLat, MinLon);
		Height = LatLonDistance(MinLat, MinLon, MinLat, MaxLon);
	}

	double MinLat;
	double MaxLat;
	double MinLon;
	double MaxLon;

	double Length;
	double Height;
};

struct FNode
{
	FNode(int64 inID, double Lat, double Lon, const FLatLonCoordinate& LatLon)
	{
		ID = inID;

		double X = (Lat - LatLon.MinLat) / (LatLon.MaxLat - LatLon.MinLat) * LatLon.Length;
		double Y = (Lon - LatLon.MinLon) / (LatLon.MaxLon - LatLon.MinLon) * LatLon.Height;

		Location = FVector(X, Y, 0.0);
	}

	int64 ID;
	FVector Location;
};

FVector FindLocationAtPointID(int64 ID, const TArray<FNode>& Points)
{
	for (const FNode& Point : Points)
	{
		if (Point.ID == ID)
		{
			return Point.Location;
		}
	}

	return FVector::ZeroVector;
}

void ParseBounds(FLatLonCoordinate& LatLon, const FXmlNode* Node)
{
	double MinLat = FCString::Atod(*(Node->GetAttribute("minlat")));
	double MinLon = FCString::Atod(*(Node->GetAttribute("minlon")));
	double MaxLat = FCString::Atod(*(Node->GetAttribute("maxlat")));
	double MaxLon = FCString::Atod(*(Node->GetAttribute("maxlon")));

	LatLon.Fill(MinLat, MaxLat, MinLon, MaxLon);
}

void ParseNode(TArray<FNode>& Nodes, const FXmlNode* Node, const FLatLonCoordinate& LatLon)
{
	int64 ID = FCString::Atoi64(*(Node->GetAttribute("id")));
	double Lat = FCString::Atod(*(Node->GetAttribute("lat")));
	double Lon = FCString::Atod(*(Node->GetAttribute("lon")));

	Nodes.Add(FNode(ID, Lat, Lon, LatLon));
}

void ParseWay(TArray<FWay>& Ways, const FXmlNode* Node, const TArray<FNode>& Points)
{
	FWay Way;
	Way.ID = FCString::Atoi64(*(Node->GetAttribute("id")));

	for (const FXmlNode* ChildNode : Node->GetChildrenNodes())
	{
		const FString& NodeTag = ChildNode->GetTag();

		if (NodeTag == TEXT("tag"))
		{
			FString Key = ChildNode->GetAttribute("k");
			FString Value = ChildNode->GetAttribute("v");

			if		(Key == TEXT("highway"))		{ Way.Type = Value; }
			else if (Key == TEXT("name"))			{ Way.Name = Value; }
			else if (Key == TEXT("name:en"))		{ Way.NameEn = Value; }
			else if (Key == TEXT("oneway"))			{ Way.OneWay = Value; }
		}

		else if (NodeTag == TEXT("nd"))
		{
			FString PointIDStr = ChildNode->GetAttribute("ref");
			int64 PointID = FCString::Atoi64(*PointIDStr);
			FVector Location = FindLocationAtPointID(PointID, Points);

			Way.Points.Add(Location);
		}
			
	}

	Ways.Add(Way);
}

void OSM_Parser::ParseFile(const FString& FilePath, TArray<FWay>& OutWays)
{
	UE_LOG(LogOSMParser, Log, TEXT("Loading file \"%s\""), *FilePath);

	TArray<FNode> Nodes;
	FLatLonCoordinate LatLon;

	FXmlFile XmlFile;
	if (XmlFile.LoadFile(FilePath))
	{
		FXmlNode* RootNode = XmlFile.GetRootNode();
		if (RootNode)
		{
			for (const FXmlNode* Node : RootNode->GetChildrenNodes())
			{
				const FString& NodeTag = Node->GetTag();

				if (NodeTag == TEXT("bounds"))
				{
					ParseBounds(LatLon, Node);
				}

				else if (NodeTag == TEXT("node"))
				{
					ParseNode(Nodes, Node, LatLon);
				}

				else if (NodeTag == TEXT("way"))
				{
					ParseWay(OutWays, Node, Nodes);
				}
			}
		}

		else
		{
			UE_LOG(LogOSMParser, Error, TEXT("File doesn`t contain a root."));
		}


		// log result 
		for (FWay& Way : OutWays)
		{
			UE_LOG(LogOSMParser, Log, TEXT("%lli, %s, %s, %s, %s \n"), Way.ID, *Way.Name, *Way.NameEn, *Way.Type, *Way.OneWay);

			for (FVector n : Way.Points)
			{
				UE_LOG(LogOSMParser, Log, TEXT("%s,"), *n.ToString());
			}

			UE_LOG(LogOSMParser, Log, TEXT("\n ------------------------------------------------"));
		}
		
		for (FNode& n : Nodes)
		{	
			FString s = FString::Printf(TEXT("%lli, %s"), n.ID, *n.Location.ToString());
			UE_LOG(LogOSMParser, Log, TEXT("%s"), *s);
			UE_LOG(LogOSMParser, Log, TEXT("\n ------------------------------------------------"));
		}
	}

	else
	{
		UE_LOG(LogOSMParser, Error, TEXT("Failed to load osm file \"%s\""), *FilePath);
	}
}