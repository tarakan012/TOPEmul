#pragma once




tm now();
ostream & formatDateTime(ostream & out, const tm & t, const char * fmt);
string dataTimeToString(const tm & t, const char * format);


