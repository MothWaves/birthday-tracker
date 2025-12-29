#ifndef ZODIAC_H_
#define ZODIAC_H_

#include "types.h"

/*
| Sign        | Range                     | Ordinal Range (Regular) | Ordinal Range (Leap Year) |
|-------------+---------------------------+-------------------------+---------------------------|
| Aquarius    | January 20 - February 18  | 20 - 49                 | 20 - 49                   |
| Pisces      | February 19 - March 20    | 50 - 79                 | 50 - 80                   |
| Aries       | March 21 - April 19       | 80 - 109                | 81 - 110                  |
| Taurus      | April 20 - May 20         | 110 - 140               | 111 - 141                 |
| Gemini      | May 21 - June 21          | 141 - 172               | 142 - 173                 |
| Cancer      | June 22 - July 22         | 173 - 203               | 174 - 204                 |
| Leo         | July 23 - August 22       | 204 - 234               | 205 - 235                 |
| Virgo       | August 23 - September 22  | 235 - 265               | 236 - 266                 |
| Libra       | September 23 - October 23 | 266 - 296               | 267 - 297                 |
| Scorpio     | October 24 - November 21  | 297 - 325               | 298 - 326                 |
| Sagittarius | November 22 - December 21 | 326 - 355               | 327 - 356                 |
| Capricorn   | December 22 - January 19  | 356 - 19                | 357 - 19                  |
 */
typedef enum {
    AQUARIUS,
    PISCES,
    ARIES,
    TAURUS,
    GEMINI,
    CANCER,
    LEO,
    VIRGO,
    LIBRA,
    SCORPIO,
    SAGITTARIUS,
    CAPRICORN
} zodiac;

zodiac getZodiac(birthday_t birthday);
char *zodiacString(zodiac sign);

#endif // ZODIAC_H_
