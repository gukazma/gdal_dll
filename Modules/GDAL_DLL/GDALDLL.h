#pragma once
#ifdef DLL_EXPORTS
#    define API_CLASSEXT extern "C" _declspec(dllexport)
#    define API_STDEXT extern "C" _declspec(dllexport)
#else
#    define API_CLASSEXT extern "C" _declspec(dllimport)
#    define API_STDEXT extern "C" _declspec(dllimport)
#endif
API_STDEXT void CoordinateTransformation(double* input, int intputEPSG, int outputEPSG);