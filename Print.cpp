/*
 Print.cpp - Base class that provides print() and println()
 Copyright (c) 2008 David A. Mellis.  All right reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 Modified 23 November 2006 by David A. Mellis
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "Arduino.h"

#include "Print.h"

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
size_t Print::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  while (size--) {
    n += write(*buffer++);
  }
  return n;
}

//size_t Print::print(unsigned char b, int base)
//{
//  return print((unsigned long) b, base);
//}
//
//size_t Print::print(int n, int base)
//{
//  return print((long) n, base);
//}
//
//size_t Print::print(unsigned int n, int base)
//{
//  return print((unsigned long) n, base);
//}
//
//size_t Print::print(long n, int base)
//{
//  if (base == 0) {
//    return write(n);
//  } else if (base == 10) {
//    if (n < 0) {
//      int t = print('-');
//      n = -n;
//      return printNumber(n, 10) + t;
//    }
//    return printNumber(n, 10);
//  } else {
//    return printNumber(n, base);
//  }
//}
//
//size_t Print::print(unsigned long n, int base)
//{
//  if (base == 0) return write(n);
//  else return printNumber(n, base);
//}

//size_t Print::print(double n, int digits)
//{
//  return printFloat(n, digits);
//}

//size_t Print::println(unsigned char b, int base)
//{
//  size_t n = print(b, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(int num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(unsigned int num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(long num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(unsigned long num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}

//size_t Print::println(double num, int digits)
//{
//  size_t n = print(num, digits);
//  n += println();
//  return n;
//}


// Private Methods /////////////////////////////////////////////////////////////

//size_t Print::printNumber(unsigned long n, uint8_t base) {
//  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
//  char *str = &buf[sizeof(buf) - 1];
//
//  *str = '\0';
//
//  // prevent crash if called with base == 1
//  if (base < 2) base = 10;
//
//  do {
//    unsigned long m = n;
//    n /= base;
//    char c = m - base * n;
//    *--str = c < 10 ? c + '0' : c + 'A' - 10;
//  } while(n);
//
//  return write(str);
//}