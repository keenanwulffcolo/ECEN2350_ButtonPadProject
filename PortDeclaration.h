#ifndef PORTDECLARATION_H_
#define PORTDECLARATION_H_

#include <stdint.h>
// Standard usage *PORT_IN(1) = BIT1
inline uint8_t* PORT_IN (uint8_t x)
{
    return (uint8_t*)(0x40004C00 + (2*((x-1)/2) * 0x10) + (x-1)%2);
}
inline uint8_t* PORT_OUT (uint8_t x)
{
    return (PORT_IN(x) + 0x2);
}
inline uint8_t* PORT_DIR (uint8_t x)
{
    return (PORT_IN(x) + 0x4);
}
inline uint8_t* PORT_REN (uint8_t x)
{
    return (PORT_IN(x) + 0x6);
}
inline uint8_t* PORT_SEL0 (uint8_t x)
{
    return (PORT_IN(x) + 0xA);
}
inline uint8_t* PORT_SEL1 (uint8_t x)
{
    return (PORT_IN(x) + 0xC);
}
inline uint8_t* PORT_IES (uint8_t x)
{
    return (PORT_IN(x) + 0x18);
}
inline uint8_t* PORT_IE (uint8_t x)
{
    return (PORT_IN(x) + 0x1A);
}
inline uint8_t* PORT_IFG (uint8_t x)
{
    return (PORT_IN(x) + 0x1C);
}
#endif /* PORTDECLARATION_H_ */
