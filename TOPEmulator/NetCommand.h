#pragma once
#include "stdafx.h"

#define MESSAGE_DEF(name, id, description) const int name = id

// (S)erver -> (C)lient

MESSAGE_DEF(CMD_SC_CHAPSTR, 940, first.packet);