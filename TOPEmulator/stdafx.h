// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once
#define NOMINMAX
#include "targetver.h"
#include "LogHundler.h"
#include "boost\asio.hpp"
#include "boost\format.hpp"
#include "boost\endian\conversion.hpp"
#include "boost\log\trivial.hpp"
#include "boost\log\sources\global_logger_storage.hpp"
#include "CommCommand.h"
#include "Player.h"
#include"Typedef.h"
#include "Packet.h"
#include "Point.h"
#include "pqxx\pqxx"
#include "NetCommand.h"
#include "NetRetCommand.h"
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
#include <iomanip>
#include <memory>
#include <thread>
#include <vector>

using namespace boost;


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
