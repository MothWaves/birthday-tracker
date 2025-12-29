#include "types.h"
#include "zodiac.h"
#include <stdio.h>
#include <sys/types.h>
#include "sort.h"


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



zodiac getZodiac(birthday_t birthday) {
  int offset = 0;
  if (isLeap(birthday.year_of_birth)) {
    offset = 1;
  }
  int ordinal = calculate_ordinal(birthday.day, birthday.month, birthday.year_of_birth);
  // Aquarius
  if (ordinal >= 20 && ordinal <= 49) {
    return AQUARIUS;
  }
  // Pisces
  else if (ordinal >= 50 && ordinal <= ( 79 + offset ) ) {
    return PISCES;
  }
  // Aries
  else if (ordinal >= ( 80 + offset )  && ordinal <= ( 109 + offset ) ) {
    return ARIES;
  }
  // Taurus
  else if (ordinal >= ( 110 + offset )  && ordinal <= ( 140 + offset ) ) {
    return TAURUS;
  }
  // Gemini
  else if (ordinal >= ( 141 + offset )  && ordinal <= ( 172 + offset ) ) {
    return GEMINI;
  }
  // Cancer
  else if (ordinal >= ( 173 + offset )  && ordinal <= ( 203 + offset ) ) {
    return CANCER;
  }
  // Leo
  else if (ordinal >= ( 204 + offset )  && ordinal <= ( 234 + offset ) ) {
    return LEO;
  }
  // Virgo
  else if (ordinal >= ( 235 + offset )  && ordinal <= ( 265 + offset ) ) {
    return VIRGO;
  }
  // Libra
  else if (ordinal >= ( 266 + offset )  && ordinal <= ( 296 + offset ) ) {
    return LIBRA;
  }
  // Scorpio
  else if (ordinal >= ( 297 + offset )  && ordinal <= ( 325 + offset ) ) {
    return SCORPIO;
  }
  // Sagittarius
  else if (ordinal >= ( 326 + offset )  && ordinal <= ( 355 + offset ) ) {
    return SAGITTARIUS;
  }
  // Capricorn
  else {
    return CAPRICORN;
  }
}


char *zodiacString(zodiac sign) {
  switch (sign) {
    case AQUARIUS:
      return "Aquarius";
    break;
    case PISCES:
      return "Pisces";
    break;
    case ARIES:
      return "Aries";
    break;
    case TAURUS:
      return "Taurus";
    break;
    case GEMINI:
      return "Gemini";
    break;
    case CANCER:
      return "Cancer";
    break;
    case LEO:
      return "Leo";
    break;
    case VIRGO:
      return "Virgo";
    break;
    case LIBRA:
      return "Libra";
    break;
    case SCORPIO:
      return "Scorpio";
    break;
    case SAGITTARIUS:
      return "Sagittarius";
    break;
    case CAPRICORN:
      return "Capricorn";
    break;
    default:
        printf("ERROR: Non existent zodiac.");
    break;
  }
  return "ERROR_ZODIAC";
}
