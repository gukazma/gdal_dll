#include "GDALDLL.h"
#include  <gdal.h>
#include <gdal_priv.h>
#include <iostream>
void GDAL_DLL() {
    // ע�����е�GDAL����
    GDALAllRegister();
    // gdal���ݿ�λ��
    std::string gdaldataPath = "./gdal_data";
    std::string projdataPath = "./proj";
    const char* paths[]      = {gdaldataPath.c_str(), projdataPath.c_str(), nullptr};
    OSRSetPROJSearchPaths(paths);
    CPLSetConfigOption("GDAL_DATA", gdaldataPath.c_str());
    // ��դ�����ݼ�
    GDALDataset* poDataset = (GDALDataset*)GDALOpen("your_raster_dataset.tif", GA_ReadOnly);
    if (poDataset == NULL) {
        printf("Error: Unable to open the raster dataset.\n");
        return ;
    }

    // ��ȡ���ݼ��ĵ���任��Ϣ
    double adfGeoTransform[6];
    poDataset->GetGeoTransform(adfGeoTransform);

    // ��ȡ���ݼ���ͶӰ��Ϣ
    const char* pszProjection = poDataset->GetProjectionRef();

    // �������任��Ϣ
    printf("GeoTransform:\n");
    for (int i = 0; i < 6; i++) {
        printf("%f ", adfGeoTransform[i]);
    }
    printf("\n");

    // ���ͶӰ��Ϣ
    printf("Projection: %s\n", pszProjection);

    // �ͷ����ݼ�
    GDALClose(poDataset);
}