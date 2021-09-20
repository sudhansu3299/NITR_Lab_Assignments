#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


#define FIFO_FILE "MYFIFO"

int main() {
   int fd;
   int end_pro;
   int stringlen;
   char readbuffer[80];
   char end_str[5];
   printf("FIFO_CLIENT: Send messages, to end the loop enter \"bye\"\n");
   fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
   strcpy(end_str, "bye");
   
   while (1) {
      printf("Enter string: ");
      fgets(readbuffer, sizeof(readbuffer), stdin);
      stringlen = strlen(readbuffer);
      readbuffer[stringlen - 1] = '\0';
      end_pro = strcmp(readbuffer, end_str);
      
      if (end_pro != 0) {
         write(fd, readbuffer, strlen(readbuffer));
      } else {
         write(fd, readbuffer, strlen(readbuffer));
         close(fd);
         break;
      }
   }
   return 0;
}
