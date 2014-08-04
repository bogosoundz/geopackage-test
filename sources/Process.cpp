/*
 * Process.cpp
 *
 *  Created on: 20/05/2014
 *      Author: bogo
 */

#include "Process.h"
#include <gdal_priv.h>
#include <gdal.h>

using namespace std::chrono;

Process::Process(std::string dataSource, std::string layerName) {
	// TODO Auto-generated constructor stub
	poDS=NULL;
	layer=NULL;
	std::string attributeFilter="";
	spatialFilterGeom=NULL;
	spatialFilterEnvelope=NULL;
	int loadTime=0;
	int executeTime=0;

	openData(dataSource, layerName);
}

Process::~Process() {
	if(poDS!=NULL)
	{
		delete poDS;
	}
	if(spatialFilterGeom!=NULL)
	{
		delete spatialFilterGeom;
	}
}

/*void printOGRDrivers()
{
	OGRSFDriverRegistrar *poR = OGRSFDriverRegistrar::GetRegistrar();
	int n1 = poR->GetDriverCount();

	printf( "Driver Count: %d \n", n1 );

	for (int i = 0; i < n1; ++i)
	{
		OGRSFDriver *driver= poR->GetDriver(i);
		std::string name = driver->GetName();
		printf("Driver Name: %s \n", name.c_str());
		delete driver;
	}
	delete poR;
}*/



void Process::openData( std::string file, std::string layerName)
{
	auto start = steady_clock::now();

	GDALAllRegister();

	poDS = (GDALDataset*) GDALOpenEx(file.c_str(), GDAL_OF_READONLY | GDAL_OF_VECTOR, NULL, NULL, NULL);
	if( poDS == NULL )
	{
		printf( "Open failed.\n" );
		exit( 1 );
	}

	if(layerName.empty())
	{
		layer = poDS->GetLayer(0);
	}
	else
	{
		layer = poDS->GetLayerByName(layerName.c_str());
	}

	//printf("%s \n", layer->GetName());

	auto end = steady_clock::now() ;

	loadTime =(duration_cast<milliseconds>(end-start).count());

}

int Process::getFeaturesCount()
{
	int count = layer->GetFeatureCount(1);

	return count;
}



void Process::execute()
{
	auto start = steady_clock::now();

	iterateOverFeatures();

	auto end = steady_clock::now() ;

	executeTime=(duration_cast<milliseconds>(end-start).count());

}
void Process::iterateOverFeatures()
{
	if(!attributeFilter.empty())
	{
		layer->SetAttributeFilter(attributeFilter.c_str());
	}
	if(spatialFilterGeom!=NULL)
	{
		layer->SetSpatialFilter(spatialFilterGeom);
	}
	if(spatialFilterEnvelope!=NULL)
	{
		layer->SetSpatialFilterRect(spatialFilterEnvelope->MinX,spatialFilterEnvelope->MinY,spatialFilterEnvelope->MaxX,spatialFilterEnvelope->MaxY);
	}
    OGRFeature *poFeature=NULL;

    layer->ResetReading();
    int i=0;
    while( (poFeature = layer->GetNextFeature()) != NULL )
    {
    	OGRFeatureDefn *poFDefn = layer->GetLayerDefn();
		int iField;
    }
   // delete poFeature;
}


