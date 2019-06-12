#ifndef __diskio_h

#define __diskio_h

int write_block(int block, void *ptr_to_mem);
void *read_block(int block);

unsigned int init_disk(char *diskname, int blocksize);

#endif