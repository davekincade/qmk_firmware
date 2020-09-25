/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once


#define USE_I2C

#define MASTER_RIGHT
// #define MASTER_RIGHT
//#define EE_HANDS
// Rows are doubled-up

#define MATRIX_COL_PINS { B3, B1, F7, F6, F5, F4 }
#define MATRIX_ROW_PINS { E6, D7, C6, D4, B4 }
#define RGB_DI_PIN B2
