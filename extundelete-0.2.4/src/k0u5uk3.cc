#include "config.h"
#include "block.h"

/* C++ libraries */
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cerrno>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <new>
#include <set>
#include <sstream>
#include <stdint.h>
#include <vector>

/* POSIX libraries */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

/* GNU headers */
#ifndef HAVE_GETOPT_H
#define getopt_long(a,b,c,d,e)  getopt((a),(b),(c))
struct option {
	const char *name;
	int has_arg;
	int *flag;
	int val;
};
#else
#include <getopt.h>
#endif

/* ext3/4 libraries */
#include <ext2fs/ext2fs.h>
#include "extundelete.h"

#ifndef EXT2_FLAG_64BITS
#define EXT2_FLAG_64BITS 0x20000
#endif

void print_directory_inode(ext2_filsys fs, struct ext2_inode *inode, ext2_ino_t /*ino*/); 

int main(){
   ext2_filsys fs;
   errcode_t errcode;
   io_manager io_mgr = unix_io_manager;

   errcode = ext2fs_open("/home/vagrant/disk", EXT2_FLAG_64BITS, 0, 0, io_mgr, &fs);
   if(errcode){
      printf("ext2fs_open error\n");
   }

   //print_inode(fs, 12);
   struct ext2_inode *inode;
   ext2_ino_t ino = EXT2_ROOT_INO;
   inode = (struct ext2_inode *) operator new(EXT2_INODE_SIZE(fs->super)); 
   ext2fs_read_inode_full (fs, ino, inode, EXT2_INODE_SIZE(fs->super));    
   print_directory_inode(fs, inode, ino);
   delete inode;

   errcode = ext2fs_close(fs);
   if(errcode){
      printf("ext2fs_close error\n");
   }
}


