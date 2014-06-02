#include <stdio.h>
#include "ogrsf_frmts.h"
#include "main.h"
#include <Process.h> // C++11

int main(int argc, char * argv[]) {

	OGRRegisterAll();

/*	printf(" \nGPKG Full \n");
	executeProcess("/dados/temp/geopackage/desflorestamento.gpkg");
	printf(" \nPG Full \n");
	executeProcess("PG:dbname=geopackage host=localhost user=postgres password=postgres","public.prodes_desflorestamento");
	printf(" \nSHP Full \n");
	executeProcess("/dados/temp/geopackage/desflorestamento.shp");

	printf(" \nGPKG Attribute Filter \n");
	executeProcess("/dados/temp/geopackage/desflorestamento.gpkg","","data = '2003-01-01'");
	printf(" \nPG Attribute Filter \n");
	executeProcess("PG:dbname=terrabrasilis host=chronos port=5433 user=postgres","public.prodes_desflorestamento","data = '2003-01-01'");
	printf(" \nSHP Attribute Filter \n");
	executeProcess("/dados/temp/geopackage/desflorestamento.shp","","data = '2003-01-01'");*/

	OGREnvelope *env = new OGREnvelope();

	env->MinX =-73.7772445678711;
	env->MinY =-17.2080955505371;
	env->MaxX =-43.9992790222168;
	env->MaxY =5.16189336776733;

	printf(" \nGPKG Spatial Filter BBOX\n");
	executeProcess("/dados/temp/geopackage/desflorestamento.gpkg","","",env);
	printf(" \nPG Spatial Filter BBOX \n");
	executeProcess("PG:dbname=terrabrasilis host=chronos port=5433 user=postgres","public.prodes_desflorestamento","",env);
	printf(" \nSHP Spatial Filter BBOX \n");
	executeProcess("/dados/temp/geopackage/desflorestamento.shp","","",env);

	return 0;
}
void executeProcess(std::string datasource, std::string layerName, std::string attributeFilter, OGREnvelope* spatialFilterEnvelope, OGRGeometry* spatialFilterGeom)
{
	Process *p = new Process(datasource, layerName);

	int loadTime = p->getLoadTime();
	if(!attributeFilter.empty())
	{
		p->setAttributeFilter(attributeFilter);
	}
	if(spatialFilterEnvelope!=0)
	{
		p->setSpatialFilterEnvelope(spatialFilterEnvelope);
	}
	if(spatialFilterGeom!=0)
	{
		p->setSpatialFilterGeom(spatialFilterGeom);
	}

	p->execute();

	int executeTime = p->getExecuteTime();

	printf("Load Time: %d \n",loadTime);
	printf("Execute Time: %d \n",executeTime);
	delete p;
}
