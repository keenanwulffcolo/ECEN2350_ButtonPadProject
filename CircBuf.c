//Circbuf.c
#include "CircBuf.h"
CB_status InitializeBuffer(CircBuf * buf, uint32_t length){
	buf->buffer = (uint8_t*)malloc(length);
	if (! buf->buffer){
		return CB_INIT_FAILURE;
	}
	buf->length = length;
	buf->num_items = 0;
	buf->head = buf->buffer;
	buf->tail = buf->buffer;
	return CB_INIT_SUCCESS;
}
static inline uint8_t * nextItem(CircBuf * buf, uint8_t * ptr){
	if(ptr == buf->buffer + buf->length){
		return(buf->buffer);
	}
	else{
		return(ptr++);
	}
}
static inline uint8_t * prevItem(CircBuf * buf, uint8_t * ptr){
	if(ptr == buf->buffer){
		return(buf->buffer + buf->length);
	}
	else{
		return(ptr--);
	}
}
void ClearBuffer(CircBuf * buf){
	buf->head = buf->buffer;//reset all data by restoring buffer to initial state
	buf->tail = buf->buffer;
	buf->num_items = 0;
}
void DeleteBuffer(CircBuf * buf){
	free(buf->buffer);
}
int8_t BufferFull(CircBuf * buf){
	if(buf->num_items == buf->length){//if the buffer is full, throw error
		return(1);
	}
	return(0);
}
int8_t BufferEmpty(CircBuf * buf){
	int8_t errorInt = 0;
	if(buf->num_items == 0){//if the buffer is empty, throw error
		errorInt = 1;
	}
	return(errorInt);
}
void AddItemToBuffer(CircBuf * buf, uint8_t item){
	// conditionals for moving tail in various cases
	if(buf->num_items != 0){}//empty if statement for adding first item to buffer
		buf->tail = nextItem(buf, buf->tail);
	}
	//actually add the item to the buffer
	*buf->tail = item;
	if(buf->num_items < buf->length){ // only incriment numitems if buffer isn't full
		buf->num_items++;
	}
}
void RemoveItemFromBuffer(CircBuf * buf){
	// conditionals for moving headin various cases
	buf->head = nextItem(buf, buf->head);
	buf->num_items--;
}



