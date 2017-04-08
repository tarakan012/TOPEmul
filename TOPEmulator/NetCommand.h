#pragma once

#define MESSAGE_DEF(name, id, description) const int name = id

// (S)erver -> (C)lient

MESSAGE_DEF(CMD_SC_CHAPSTR, 940, first.packet);
MESSAGE_DEF(CMD_SC_LOGIN, 931, login.errror);
MESSAGE_DEF(CMD_SC_CREATEPASSWORD2, 941, security.pasword);

// (C)lient -> (S)erver
MESSAGE_DEF(CMD_CS_LOGIN, 431, login);
MESSAGE_DEF(CMD_CS_CREATEPASSWORD2, 346, security.pasword);
MESSAGE_DEF(CMD_CS_NEWCHA, 935, newcharacter);

