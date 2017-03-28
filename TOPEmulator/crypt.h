#pragma once


#ifndef CRYPT_H
#define CRYPT_H
#define _CRT_SECURE_NO_WARNINGS


#include "des.h"

using namespace std;

string  EncryptPassword(string&, string&);
#endif