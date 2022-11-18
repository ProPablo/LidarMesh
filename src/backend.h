#pragma once

#include <string>


struct ReconDTO {
	std::string fileName;
	std::string outputFileDir;

	float wt_fitting = 0.2; //lower == lower overhead
	float wt_coverage = 0.1; //lower = lower overhead
	float complexity = 0.7; //higher = lower overhead

	//  // Set probability to miss the largest primitive at each iteration.
	//parameters.probability = 0.05;
	//// Detect shapes with at least 200 points.
	//parameters.min_points = 200;
	//// Set maximum Euclidean distance between a point and a shape.
	//parameters.epsilon = 0.002;
	//// Set maximum Euclidean distance between points to be clustered.
	//parameters.cluster_epsilon = 0.01;
	int ransacMinPoints =200;
	float ransacEpsilon = 0.002;
	float ransacClusterEpsilon = 0.01;
	float ransacProbability = 0.1;
	//Need probability
};

//bool openFile(std::string& outPath);
bool openFile(std::string& outPath, bool isFolder = false);
int runRecon(ReconDTO dto);
void threadUpdateStatus(std::string& statusRef);
