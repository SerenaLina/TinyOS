#include "include/disk.h"

static struct virtq_desc desc_table[VIRTQ_DESC_NUM]__attribute__((aligned(16)));
void disk_init(void)
{
    volatile unsigned int *magic = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_MAGIC);
    volatile unsigned int *device_id = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_DEVICE_ID);
    volatile unsigned int *version = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_VERSION);
    volatile unsigned int *queue_sel = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_QUEUE_SEL);
    volatile unsigned int *queue_num = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_QUEUE_NUM);
    volatile unsigned int *queue_ready = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_QUEUE_READY);

    uart_puts("Magic: ");
    uart_puthex(*magic);
    uart_puts("\r\n");
    
    uart_puts("Device ID: ");
    uart_puthex(*device_id);
    uart_puts("\r\n");
    
    uart_puts("Version: ");
    uart_puthex(*version);
    uart_puts("\r\n");


    if(*magic != 0x74726976)
    {
        uart_puts("Error: Virtio block device not found!\n\r");
        return ;
    }
    else
    {
        uart_puts("Virtio block device found!\n\r");
    }
    if(*device_id != 0x00000000)
    {
        uart_puts("Error: Device is not a block device!\n\r");
        return ;
    }
    else
    {
        uart_puts("Device is a block device!\n\r");
    }
    if(*version!=0x00000002 && *version!=0x00000001)
    {
        uart_puts("Error: Device version is not supported!\n\r");
        return ;
    }
    else
    {
        uart_puts("Device version is supported!\n\r");
    }
    *queue_sel = 0;
    *queue_num = 8;
    *queue_ready = 1;

    volatile uint32_t *desc_low = (uint32_t *)(VIRTIO_BLK_BASE + VIRTIO_REG_QUEUE_DESC_LOW);
    volatile uint32_t *desc_high = (uint32_t *)(VIRTIO_BLK_BASE + VIRTIO_REG_QUEUE_DESC_HIGH);
    *desc_low = (uint32_t)((uint64_t)desc_table & 0xFFFFFFFF);
    *desc_high = (uint32_t)((uint64_t)desc_table >> 32);
    uart_puts("Virtio block device initialized!\n\r");
}

int disk_read(void *buf,unsigned int sector,unsigned int count)
{
    //Request header.
    struct virtio_blk_req{
        uint32_t type;
        uint32_t reserved;
        uint64_t sector;
    }req;

    req.type = 0;
    req.sector = sector;
    struct virtq_desc *desc = desc_table;
    /*
    We need three describetor.
    */
    desc[0].addr = (uint64_t)&req;
    desc[0].len = sizeof(req);
    desc[0].flags = VIRTQ_DESC_F_NEXT;
    desc[0].next = 1;

    desc[1].addr = (uint64_t)buf;
    desc[1].len = count * 512;
    desc[1].flags = VIRTQ_DESC_F_WRITE | VIRTQ_DESC_F_NEXT;
    desc[1].next = 2;

    uint8_t status;
    desc[2].addr =(uint64_t)&status;
    desc[2].len = 1;
    desc[2].flags = VIRTQ_DESC_F_WRITE;
    desc[2].next = 0;

    volatile uint32_t *notify = (uint32_t *)(VIRTIO_BLK_BASE + VIRTIO_REG_QUEUE_NOTIFY);
    *notify = 0;

    while(status == 0)
    ;

    return (status == 0x00) ? 0 : -1; //0 successful
}

//Noting special about this device and registers.
int disk_write(void *buf,unsigned int sector,unsigned int count)
{
    struct virtio_blk_req{
        uint32_t type;
        uint32_t reserved;
        uint64_t sector;
    }req;

    req.type = 1;
    req.sector = sector;
    struct virtq_desc *desc = desc_table;

    desc[0].addr = (uint64_t)&req;
    desc[0].len = sizeof(req);
    desc[0].flags = VIRTQ_DESC_F_NEXT;
    desc[0].next = 1;

    desc[1].addr = (uint64_t)buf;
    desc[1].len = count * 512;
    desc[1].flags = VIRTQ_DESC_F_NEXT;
    desc[1].next = 2;

    uint8_t status;
    desc[2].addr = (uint64_t)&status;
    desc[2].len = 1;
    desc[2].flags = VIRTQ_DESC_F_WRITE;
    desc[2].next = 0;

    volatile uint32_t *notify = (uint32_t *)(VIRTIO_BLK_BASE + VIRTIO_REG_QUEUE_NOTIFY);
    *notify = 0;
    while(status == 0)
    ;
    return (status == 0x00)? 0 : -1;
}

