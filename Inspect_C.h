#ifndef _INSPECT_C_H
#define _INSPECT_C_H

#define DLL_API __declspec(dllexport)
//参数1 ip :192.100.100.XX
//参数2 port：60000,60001,60002,60003
//参数3 socid :0-9
extern "C"
{
	DLL_API int Insp_Init(const char *ip,int port=60000);
	DLL_API int Insp_Close(int port=60000);
	DLL_API int Insp_SetStart(int cam1,int cam2,int cam3,int cam4,int port=60000);
	DLL_API int Insp_GetStart(int &cam1,int &cam2,int &cam3,int &cam4,int port=60000);
	DLL_API int Insp_GetRlt(int &cam1,int &cam2,int &cam3,int &cam4,int &RunSts,int port=60000);
	DLL_API int Insp_GetSts(int &cam1,int &cam2,int &cam3,int &cam4,int port=60000);
	DLL_API int Insp_ResetSts(int cam1,int cam2,int cam3,int cam4,int port=600000);
	DLL_API int Insp_WaitRlt(int cam1,int cam2,int cam3,int cam4,int port=60000);
	DLL_API int Insp_GetStaFlag(int &flag,int port=60000);
	DLL_API int Insp_SetTimeOut(int s,int port=60000);

};
#endif
