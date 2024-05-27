#include "GDALDLL.h"
#include  <gdal.h>
#include <gdal_priv.h>
#include <iostream>
#include <boost/dll.hpp>
#include <boost/filesystem.hpp>
void CoordinateTransformation(double* input, int intputEPSG, int outputEPSG)
{
    GDALAllRegister();
    boost::filesystem::path binPath = boost::dll::program_location();
    auto                    gdaldataPath = binPath.parent_path() / "gdal_data";
    auto                    projdataPath = binPath.parent_path() / "proj";
    std::string             sgdaldataPath = gdaldataPath.string(), sprojdataPath = projdataPath.string();

    const char* paths[] = {sgdaldataPath.c_str(), sprojdataPath.c_str(), nullptr};

    OSRSetPROJSearchPaths(paths);
    CPLSetConfigOption("GDAL_DATA", sgdaldataPath.c_str());

    OGRSpatialReference          oSourceSRS, oTargetSRS;
    OGRCoordinateTransformation* poCT;

    oSourceSRS.importFromEPSG(intputEPSG);
    oTargetSRS.importFromEPSG(outputEPSG);

    poCT = OGRCreateCoordinateTransformation(&oSourceSRS, &oTargetSRS);

    double x = input[0], y = input[1];
    poCT->Transform(1, &y, &x);
    input[0] = x;
    input[1] = y;
}
