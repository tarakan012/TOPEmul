// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once




#include "targetver.h"
#include "boost\asio.hpp"
#include "boost\endian\conversion.hpp"
#include "boost\log\trivial.hpp"
#include "NetCommand.h"
#include <stdio.h>
#include <tchar.h>
#include <ctime>
#include <locale>
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <iterator>
#include <sstream>

#include <memory>
#include <thread>
#include <vector>

using namespace boost;

using uShort = unsigned short;
using cChar = const char;


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������