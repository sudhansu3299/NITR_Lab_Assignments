#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>


#define FIFO_FILE "MYFIFO"

int main() {
   int fd;
   char readbuffer[80];
   char bye[10];
   int to_end;
   int read_bytes;
   
   mknod(FIFO_FILE, S_IFIFO|0640, 0);
   strcpy(bye, "bye");
   while(1) {
      fd = open(FIFO_FILE, O_RDONLY);
      read_bytes = read(fd, readbuffer, sizeof(readbuffer));
      readbuffer[read_bytes] = '\0';
      printf("Received string: \"%s\" \n", readbuffer);
      to_end = strcmp(readbuffer, bye);
      if (to_end == 0) {
         close(fd);
         break;
      }
   }
   return 0;
}
