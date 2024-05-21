#include "GDALDLL.h"
#include  <gdal.h>
#include <gdal_priv.h>
#include <iostream>
void GDAL_DLL() {
    // 注册所有的GDAL驱动
    GDALAllRegister();
    // gdal数据库位置
    std::string gdaldataPath = "./gdal_data";
    std::string projdataPath = "./proj";
    const char* paths[]      = {gdaldataPath.c_str(), projdataPath.c_str(), nullptr};
    OSRSetPROJSearchPaths(paths);
    CPLSetConfigOption("GDAL_DATA", gdaldataPath.c_str());
    // 打开栅格数据集
    GDALDataset* poDataset = (GDALDataset*)GDALOpen("your_raster_dataset.tif", GA_ReadOnly);
    if (poDataset == NULL) {
        printf("Error: Unable to open the raster dataset.\n");
        return ;
    }

    // 获取数据集的地理变换信息
    double adfGeoTransform[6];
    poDataset->GetGeoTransform(adfGeoTransform);

    // 获取数据集的投影信息
    const char* pszProjection = poDataset->GetProjectionRef();

    // 输出地理变换信息
    printf("GeoTransform:\n");
    for (int i = 0; i < 6; i++) {
        printf("%f ", adfGeoTransform[i]);
    }
    printf("\n");

    // 输出投影信息
    printf("Projection: %s\n", pszProjection);

    // 释放数据集
    GDALClose(poDataset);
}