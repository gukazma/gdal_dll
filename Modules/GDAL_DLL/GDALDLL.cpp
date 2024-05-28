#include "GDALDLL.h"
#include  <gdal.h>
#include <gdal_priv.h>
#include <iostream>
#include <boost/dll.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
void CoordinateTransformation(double* input, int intputEPSG, int outputEPSG)
{
    std::ofstream   out("D:/log.txt");
    std::streambuf* coutbuf = std::cout.rdbuf();   // 保存原始的std::cout缓冲区指针

    // 将std::cout的输出重定向到文件
    std::cout.rdbuf(out.rdbuf());

    std::cout << "input: " << input[0] << ", " << input[1] << ", " << input[2] << std::endl;
    std::cout << "inputEPSG: " << intputEPSG << std::endl;
    std::cout << "outputEPSG: " << outputEPSG << std::endl;

    std::cout << "GDALAllRegister....." << std::endl;
    GDALAllRegister();
    boost::filesystem::path binPath = boost::dll::program_location();
    auto                    gdaldataPath = binPath.parent_path() / "gdal_data";
    auto                    projdataPath = binPath.parent_path() / "proj";
    std::string             sgdaldataPath = gdaldataPath.string(), sprojdataPath = projdataPath.string();

    const char* paths[] = {sgdaldataPath.c_str(), sprojdataPath.c_str(), nullptr};

    std::cout << "OSRSetPROJSearchPaths....." << std::endl;
    std::cout << "OSRSetPROJSearchPaths 0: " << gdaldataPath.string() << std::endl;
    std::cout << "OSRSetPROJSearchPaths 1: " << projdataPath.string() << std::endl;
    OSRSetPROJSearchPaths(paths);
    CPLSetConfigOption("GDAL_DATA", sgdaldataPath.c_str());

    OGRSpatialReference          oSourceSRS, oTargetSRS;
    OGRCoordinateTransformation* poCT;

    std::cout << "importFromEPSG....." << std::endl;
    oSourceSRS.importFromEPSG(intputEPSG);
    oTargetSRS.importFromEPSG(outputEPSG);


    std::cout << "OGRCreateCoordinateTransformation....." << std::endl;
    poCT = OGRCreateCoordinateTransformation(&oSourceSRS, &oTargetSRS);

    double x = input[0], y = input[1];
    poCT->Transform(1, &y, &x);
    input[0] = x;
    input[1] = y;

    std::cout << "... OGRCreateCoordinateTransformation" << std::endl;

    std::cout << "output: " << input[0] << ", " << input[1] << ", " << input[2] << std::endl;
}
