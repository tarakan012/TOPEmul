#include "CommFunc.h"




char * LookDataString(const stNetChangeChaPart * pLook, char * szLookBuf)
{
	char szData[512];
	szLookBuf[0] = '\0';
	int nBufLen = 0;
	int nDataLen = 0;
	boost::format formStr("%d,%d");
	formStr % pLook->sTypeID % pLook->sHairID;
	strcpy(szData, formStr.str().c_str());
	nDataLen = (int)strlen(szData);
	strcat(szLookBuf, szData);
	nBufLen += nDataLen;
	SItemGrid * pGridCont;
	for (size_t i = 0; i < 10; ++i)
	{
		pGridCont = (SItemGrid *)pLook->sLink + i;
		boost::format formStr{ ";%d,%d,%d,%d,%d,%d,%d" };
		formStr % pGridCont->sID % pGridCont->sNum % pGridCont->sEndure[0] % pGridCont->sEndure[1] % pGridCont->sEnergy[0]
			% pGridCont->sEnergy[1] % atoi(&pGridCont->chForgeLv);
		strcpy(szData, formStr.str().c_str());
		nDataLen = (int)strlen(szData);
		strcat(szLookBuf, szData);
		nBufLen += nDataLen;
		for (size_t m = 0; m < 2; ++m)
		{
			boost::format formStr(",%d");
			formStr % pGridCont->GetDBParam(m);
			strcpy(szData, formStr.str().c_str());
			nDataLen = (int)strlen(szData);
			nBufLen += nDataLen;
			strcat(szLookBuf, szData);
		}
		if (pGridCont->IsInstAttrValid())
		{
			strcat(szLookBuf, ",1");
		} else
		{
			strcat(szLookBuf, ",0");
		}
	}
	return szLookBuf;
}

int SRegIterInt(std::sregex_iterator & it)
{
	std::smatch sm;
	sm = *it;
	return atoi(sm.str().c_str());
}
bool StringLookData(stNetChangeChaPart * pLook, std::string & strData)
{
	const std::regex regex("(\\d)+");
	auto world_begin = std::sregex_iterator(strData.begin(), strData.end(), regex);
	auto world_end = std::sregex_iterator();
	pLook->sTypeID = SRegIterInt(world_begin++);
	pLook->sHairID = SRegIterInt(world_begin);
	SItemGrid * pItem = 0;
	for (size_t i = 0; i < 10; ++i)
	{
		pItem = pLook->sLink + i;
		pItem->sID = 0;
		pItem->sNum = 0;
		pItem->sEndure[0] = 0;
		pItem->sEndure[1] = 0;
		pItem->sEnergy[0] = 0;
		pItem->sEnergy[1] = 0;
		pItem->chForgeLv = 0;
		for (size_t m = 0; m < 2; ++m)
		{
			pItem->SetDBParam(m, 0);
		}
		for (int k = 0; k < 5; k++)
		{
			pItem->sInstAttr[k][0] = 0;
			pItem->sInstAttr[k][1] = 0;
		}
		pLook->sVer = 111;
	}
	return true;
}