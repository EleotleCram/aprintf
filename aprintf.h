/*
 * File:   aprintf.h
 * Author: mtoele
 *
 * Created on October 4, 2014, 3:21 PM
 */

#pragma once

// Standard includes
#include <stdarg.h>

// Arduino/Platform includes
#include <Arduino.h>

int avprintf(char *str, va_list argv);
int aprintf(char *str, ...);
