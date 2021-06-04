/*
 * File:   aprintf.h
 * Author: mtoele
 *
 * Created on October 4, 2014, 3:21 PM
 */

#pragma once

int avprintf(char *str, va_list argv) {
  int i, j, count = 0;

  for (i = 0, j = 0; str[i] != '\0'; i++) {
    if (str[i] == '%') {
      count++;

      Serial.write(reinterpret_cast<const uint8_t *>(str + j), i - j);

      switch (str[++i]) {
        case 'd':
          Serial.print(va_arg(argv, int));
          break;
        case 'l':
          Serial.print(va_arg(argv, long));
          break;
        case 'f':
          Serial.print(va_arg(argv, double));
          break;
        case 'c':
          Serial.print((char)va_arg(argv, int));
          break;
        case 's':
          Serial.print(va_arg(argv, char *));
          break;
        case '%':
          Serial.print("%%");
          break;
        default:;
      };

      j = i + 1;
    }
  };

  if (i > j) {
    Serial.write(reinterpret_cast<const uint8_t *>(str + j), i - j);
  }

  return count;
}

int aprintf(char *str, ...) {
  va_list argv;

  va_start(argv, str);
  const int count = avprintf(str, argv);
  va_end(argv);

  return count;
}
