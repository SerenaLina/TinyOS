#ifndef _DISK_H
#define _DISK_H
#include "include/uart.h"

/*
Noting special about this device and registers.
*/
#define VIRTIO_BLK_BASE          0x10001000
#define VIRTIO_REG_MAGIC         0x000
#define VIRTIO_REG_VERSION       0x004
#define VIRTIO_REG_DEVICE_ID     0x008
#define VIRTIO_REG_QUEUE_SEL     0x030
#define VIRTIO_REG_QUEUE_NUM     0x034
#define VIRTIO_REG_QUEUE_READY   0x044

#define VIRTIO_REG_QUEUE_DESC_LOW  0x080
#define VIRTIO_REG_QUEUE_DESC_HIGH 0x084
#define VIRTIO_REG_QUEUE_NOTIFY     0x050

#define VIRTQ_DESC_NUM 8

#define VIRTQ_DESC_F_NEXT 1
#define VIRTQ_DESC_F_WRITE 2

struct virtq_desc
{
    uint64_t addr; //buf addr
    uint32_t len;   //len of buf.
    uint16_t flags; //desc flag.
    uint16_t next;  //next desc.
};

void disk_init(void);
int disk_read(void *buf,unsigned int sector,unsigned int count);
int disk_write(void *buf,unsigned int sector,unsigned int count);
#endif