#ifndef __BYTE_HELPER_H__
#define __BYTE_HELPER_H__

bool exctractByte(unsigned int bytes, unsigned char position){
  return (bytes & (0x1 << position)) >> position;
}

#endif