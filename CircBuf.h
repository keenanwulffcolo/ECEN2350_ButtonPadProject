//Circbuf.h
#ifndef CIRCBUF_H_
#define CIRCBUF_H_
#include "msp.h"
#include <stdlib.h>
#include <stdint.h>
typedef enum {
	CB_INIT_SUCCESS = 0,
	CB_INIT_FAILURE = 1,
}CB_status;
typedef struct CircBuf_t{
	volatile uint8_t * head; // Pointer to first item
	volatile uint8_t * tail; // Pointer to last item
	volatile uint32_t num_items; // Number of items in buffer
	volatile uint32_t length; // How large the buffer should be (items)
	uint8_t * buffer; // Pointer to beginning of buffer in heap
} CircBuf;
void ClearBuffer(CircBuf * buf);
void DeleteBuffer(CircBuf * buf);
int8_t BufferFull(CircBuf * buf);
int8_t BufferEmpty(CircBuf * buf);
void AddItemToBuffer(CircBuf * buf, uint8_t item);
void RemoveItemFromBuffer(CircBuf * buf);
CB_status InitializeBuffer(CircBuf * buf, uint32_t length);
#endif /* CIRCBUF_H_ */
