//
// Created by yhood on 31/10/2021.
//

#ifndef DEV_SIMPLEANOMALYDETECTOR_H
#define DEV_SIMPLEANOMALYDETECTOR_H

#include "AnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "timeseries.h"
#include <vector>

using std::vector;
using std::string;

struct correlatedFeatures {
    string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
public:

    std::vector<correlatedFeatures> normal_model;

    SimpleAnomalyDetector();

    static vector<Point *> corrlatedCreatPoints(vector<float>, vector<float>);


    ~SimpleAnomalyDetector() override;

    virtual void learnNormal(const timeseries &ts) override;

    virtual vector<AnomalyReport> detect(const timeseries &ts) override;

    virtual vector<correlatedFeatures> getNormalModel();

    static float detectThreshold(const vector<Point *>& points, Line line);
};

#endif //DEV_SIMPLEANOMALYDETECTOR_H
