#include "CompCommand.h"
char * LookDataString(const stNetChangeChaPart * pLook, char * szLookBuf)
{
	char szData[512];
	szLookBuf[0] = '\0';
	int nBufLen = 0, nDataLen;
	strcpy(szData, "112#");
	nDataLen = (int)strlen(szData);
	strcat(szLookBuf, szData);
	nBufLen += nDataLen;

	SItemGrid * pGridCont;
	for (size_t i = 0; i < 10; i++)
	{
		pGridCont = (SItemGrid *)pLook->sLink + i;
		boost::format outFormat{ ";%d,%d,%d,%d,%d,%d,%d,%d" };
		outFormat % pGridCont->dwDBID % pGridCont->sID % pGridCont->sNum % pGridCont->sEndure[0] % pGridCont->sEndure[1] % pGridCont->sEnergy[0]
			% pGridCont->sEnergy[1] % pGridCont->chForgeLv;
		strcpy(szData, outFormat.str().c_str());
		nDataLen = (int)strlen(szData);
		strcat(szLookBuf, szData);
		nBufLen += nDataLen;

	}

	return szLookBuf;
}