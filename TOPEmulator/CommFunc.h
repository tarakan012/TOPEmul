#pragma once
#include <regex>
#include "CommCommand.h"

char * LookDataString(const stNetChangeChaPart * pLook, char * szLookBuf);
bool StringLookData(stNetChangeChaPart * pLook, std::string & strData);
int SRegIterInt(std::sregex_iterator & it);