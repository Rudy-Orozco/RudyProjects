#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
    //char filename[200];

    if(argc <= 1){
    fprintf(2, "usage: encryptFile [file ...]\nExample: encryptFile README\n\n");
    exit(1);
    }

    

    int fd = open(argv[1], 2);

    if((fd = open(argv[1], 0)) < 0){    
      fprintf(2, "encryptFile: cannot open %s\n", argv[1]);
      exit(1);
    }
    
    printf("Encrypting %s, Please Wait\n", argv[1]);

    if(encrypt(fd, 23) != 0)
    {
        printf("Failed to Encrypt file \n\n");
        return -1;
    }

    printf("Encryption done!\n");
    return 0;
}