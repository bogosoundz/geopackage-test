/*
 * Process.h
 *
 *  Created on: 20/05/2014
 *      Author: bogo
 */

#ifndef PROCESS_H_
#define PROCESS_H_
#include <chrono>
#include <string>
#include "ogrsf_frmts.h"

class Process {
public:
	Process(std::string dataSource, std::string layerName);
	virtual ~Process();
	int getFeaturesCount();

	void execute();

	std::string getAttributeFilter() {
		return attributeFilter;
	}

	void setAttributeFilter(std::string attributeFilter) {
		this->attributeFilter = attributeFilter;
	}

	const OGRGeometry* getSpatialFilterGeom() {
		return spatialFilterGeom;
	}

	void setSpatialFilterGeom(OGRGeometry* spatialFilterGeom) {
		this->spatialFilterGeom = spatialFilterGeom;
	}

	int getExecuteTime() const {
		return executeTime;
	}

	void setExecuteTime(int executeTime) {
		this->executeTime = executeTime;
	}

	int getLoadTime() const {
		return loadTime;
	}

	void setLoadTime(int loadTime) {
		this->loadTime = loadTime;
	}

	const OGREnvelope* getSpatialFilterEnvelope() const {
		return spatialFilterEnvelope;
	}

	void setSpatialFilterEnvelope(OGREnvelope* spatialFilterEnvelope) {
		this->spatialFilterEnvelope = spatialFilterEnvelope;
	}

private:
	void openData(std::string file, std::string layerName);
	void iterateOverFeatures();
	GDALDataset *poDS;
	OGRLayer *layer;
	std::string attributeFilter;
	OGRGeometry *spatialFilterGeom;
	OGREnvelope *spatialFilterEnvelope;
	int loadTime;
	int executeTime;
};

#endif /* PROCESS_H_ */
