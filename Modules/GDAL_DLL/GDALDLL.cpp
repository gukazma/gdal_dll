#include "GDALDLL.h"
#include  <gdal.h>
#include <gdal_priv.h>
#include <iostream>
void GDAL_DLL() {
    GDALAllRegister();
    std::string gdaldataPath = "D:/projects/gdal_dll/build/vs2022-x64/Tests/Debug/gdal_data";
    std::string projdataPath = "D:/projects/gdal_dll/build/vs2022-x64/Tests/Debug/proj";
    const char* paths[]      = {gdaldataPath.c_str(), projdataPath.c_str(), nullptr};
    OSRSetPROJSearchPaths(paths);
    CPLSetConfigOption("GDAL_DATA", gdaldataPath.c_str());
    OGRSpatialReference oSRS;
    oSRS.importFromEPSG(4326);
    char* pszWKT = NULL;
    oSRS.exportToPrettyWkt(&pszWKT, FALSE);
    std::cout << pszWKT << std::endl;
    CPLFree(pszWKT);
}