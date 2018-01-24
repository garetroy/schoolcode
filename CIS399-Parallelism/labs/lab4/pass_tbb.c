#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <tbb/tbb.h>

#include <openssl/md5.h>

using namespace tbb;

const char* chars="0123456789";
char success[9];
int set = 0;

// tests if a hash matches a candidate password
int test(const char* passhash, const char* passcandidate) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    
    MD5((unsigned char*)passcandidate, strlen(passcandidate), digest);
    
    char mdString[34];
    mdString[33]='\0';
    for(int i=0; i<16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned char)digest[i]);
    }
    
    return strncmp(passhash, mdString, strlen(passhash));
}

// maps a PIN to a string
void genpass(long passnum, char* passbuff) {
    passbuff[8]='\0';
    int charidx;
    int symcount=strlen(chars);
    for(int i=7; i>=0; i--) {
        charidx=passnum%symcount;
        passnum=passnum/symcount;
        passbuff[i]=chars[charidx];
    }
}

/* Return the password if matched successfully, NULL otherwise */
void password(char * digest, long element)
{
   char passmatch[9];
   genpass(element, passmatch);
   if (test(digest, passmatch) == 0) {
      strcpy(success,passmatch);
      set = 1;
   }
   return;
}

struct map_reduce
{
    char* digest;

    map_reduce(char* digest) : digest(digest) {}
    void operator() (const blocked_range<long>& range) const{
        for(long n = range.begin(); n != range.end(); n++){
            if(set == 1) continue;
            password(digest,n);
        }
    }
};

int main(int argc, char** argv)
{
    char * match;

    if (argc != 2) {
        printf("Usage: %s <password hash>\n",argv[0]);
        return 1;
    }

    task_scheduler_init init;
    map_reduce func(argv[1]);
    parallel_for(blocked_range<long>(0,99999999), func);
    
    if (success == NULL) {
       printf("\nERROR password not found for: %s\n\n", argv[0]);
    } else {
       printf("\nSUCCESS found: %s\n\n", success);
    }

    return 0;
}
