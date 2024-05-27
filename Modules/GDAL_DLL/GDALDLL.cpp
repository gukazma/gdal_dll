#include "GDALDLL.h"
#include  <gdal.h>
#include <gdal_priv.h>
#include <iostream>
#include <boost/dll.hpp>
#include <boost/filesystem.hpp>
void CoordinateTransformation(double* input, int intputEPSG, int outputEPSG)
{
    boost::filesystem::path binPath = boost::dll::program_location();
    auto                    gdaldataPath = binPath / "gdal_data";
    auto                    projdataPath = binPath / "gdal_data";
    const char* paths[] = {gdaldataPath.string().c_str(), projdataPath.string().c_str(), nullptr};

    OSRSetPROJSearchPaths(paths);
    CPLSetConfigOption("GDAL_DATA", gdaldataPath.string().c_str());

    OGRSpatialReference oSRS, tSRS;
    oSRS.importFromEPSG(intputEPSG);
    tSRS.importFromEPSG(outputEPSG);

    auto poCT = OGRCreateCoordinateTransformation(&oSRS, &tSRS);
    poCT->Transform(1, &input[0], &input[1]);
}
