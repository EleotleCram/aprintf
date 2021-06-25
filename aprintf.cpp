#include <aprintf.h>

#include <avr/pgmspace.h>

static size_t fstrlen(const __FlashStringHelper *ifsh) {
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0)
      break;
    n++;
  }
  return n;
}

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

int avprintf(const __FlashStringHelper *ifsh, va_list argv) {
  char buf[fstrlen(ifsh) + 1] = {0};
  strcpy_P(buf, reinterpret_cast<PGM_P>(ifsh));
  avprintf(buf, argv);
}

int aprintf(char *str, ...) {
  va_list argv;

  va_start(argv, str);
  const int count = avprintf(str, argv);
  va_end(argv);

  return count;
}

int aprintf(const __FlashStringHelper *str, ...) {
  va_list argv;

  va_start(argv, str);
  const int count = avprintf(str, argv);
  va_end(argv);

  return count;
}
