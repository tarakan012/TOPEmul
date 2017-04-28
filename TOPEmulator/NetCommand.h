#pragma once

#define MESSAGE_DEF(name, id, description) const int name = id

// (S)erver -> (C)lient

MESSAGE_DEF(CMD_SC_CHAPSTR, 940, send_first_packet);
MESSAGE_DEF(CMD_SC_LOGIN, 931, login.errror);
MESSAGE_DEF(CMD_SC_CREATEPASSWORD2, 941, create_security_code);
MESSAGE_DEF(CMD_SC_NEWCHA, 935, new_character);
MESSAGE_DEF(CMD_SC_ENTERMAP, 516, );
MESSAGE_DEF(CMD_SC_SAY, 501, message_say);
MESSAGE_DEF(CMD_SC_CHABEGINSEE, 504, );
MESSAGE_DEF(CMD_SC_CHAENDSEE, 505, );
MESSAGE_DEF(CMD_SC_NOTIACTION, 508, notiaction);


// (C)lient -> (S)erver
MESSAGE_DEF(CMD_CS_SAY, 1, message_say);
MESSAGE_DEF(CMD_CS_BEGINACTION, 6, begin_action);
MESSAGE_DEF(CMD_CS_LOGIN, 431, login);
MESSAGE_DEF(CMD_CS_LOGOUT, 432, logout);
MESSAGE_DEF(CMD_CS_BGNPLAY, 433, begin_play);
MESSAGE_DEF(CMD_CS_NEWCHA, 435, new_character);
MESSAGE_DEF(CMD_CS_CREATE_PASSWORD2, 346, create_security_code);
MESSAGE_DEF(CMD_CS_UPDATE_PASSWORD2, 347, update_security_code);

