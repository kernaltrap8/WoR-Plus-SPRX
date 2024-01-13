#include "main.h"
#include "show_dump.h"

 void show_dump(unsigned char *data, unsigned int len) {
  //  static const char       hex[] = "0123456789abcdef";
  //  static unsigned char    buff[67];   /* HEX  CHAR\n */
  //  unsigned char           chr,
  //                          *bytes,
  //                          *p,
  //                          *limit,
  //                          *glimit = data + len;

  //  memset(buff + 2, ' ', 48);

  //  while(data < glimit) {
  //      limit = data + 16;
  //      if(limit > glimit) {
  //          limit = glimit;
  //          memset(buff, ' ', 48);
  //      }

  //      p     = buff;
  //      bytes = p + 50;
  //      while(data < limit) {
  //          chr = *data;
  //          *p++ = hex[chr >> 4];
  //          *p++ = hex[chr & 15];
  //          p++;
  //          *bytes++ = ((chr < ' ') || (chr >= 0x7f)) ? '.' : chr;
  //          data++;
  //      }
  //      *bytes++ = '\n';
		//*bytes++ = 0;
		//printf((const char *)buff);

        // //fwrite(buff, bytes - buff, 1, stream);
		
    //}
}