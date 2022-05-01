#include "include/keys.h"

void normal_keys(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // Esc
    exit(0);
    break;

  default:
    break;
  }
}

void normal_keys_up(unsigned char key, int x, int y)
{
  switch (key)
  {
  default:
    break;
  }
}

void special_keys(int key, int x, int y)
{
  switch (key)
  {
  default:
    break;
  }
}

void special_keys_up(int key, int x, int y)
{
  switch (key)
  {
  default:
    break;
  }
}