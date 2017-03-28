#include "DataTimeToString.h"

tm now()
{
	time_t now = time(0);
	return *localtime(&now);
}

ostream & formatDateTime(ostream & out, const tm & t, const char * fmt)
{
	const time_put<char>& dataWriter = use_facet<time_put<char> >(out.getloc());
	int n = strlen(fmt);
	if (dataWriter.put(out, out, ' ', &t, fmt, fmt + n).failed())
	{
		throw runtime_error("format");
	}
	return out;
}

string dataTimeToString(const tm & t, const char * format)
{
	stringstream s;
	formatDateTime(s, t, format);
	return s.str();
}
