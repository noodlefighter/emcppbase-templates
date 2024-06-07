#pragma once

struct XbmpRes {
  unsigned int width;
  unsigned int height;
  const unsigned char *data;
  unsigned int size;
};

extern const struct XbmpRes uires_home_page;
extern const struct XbmpRes uires_battery_half;
