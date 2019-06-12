#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>

int main()
{
    //创建一个共享内存的文件描述符
    int fd = shm_open("/example", O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd == -1) return 0;
    //防止资源泄露，需要删除。执行之后共享对象仍然存活，但是不能通过名字访问
    shm_unlink("/example"); 
    
    //将共享内存对象的大小设置为4字节
    size_t size = sizeof(uint32_t);
    ftruncate(fd, size); 
    
    //两次调用mmap，把一个共享内存对象映射到两个虚拟地址上。
    int prot = PROT_READ | PROT_WRITE;    
    uint32_t *add1 = mmap(NULL, size, prot, MAP_SHARED, fd, 0);
    uint32_t *add2 = mmap(NULL, size, prot, MAP_SHARED, fd, 0);
    
    //关闭文件描述符
    close(fd);
    
    //测试，通过一个虚拟地址设置数据，两个虚拟地址得到相同的数据
    *add1 = 0xdeafbeef;
    printf("Address of add1 is: %p, value of add1 is: 0x%x\n", add1, *add1);
    printf("Address of add2 is: %p, value of add2 is: 0x%x\n", add2, *add2);
    
    return 0;
}