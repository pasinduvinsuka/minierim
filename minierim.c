#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

/*
 * minierim is a minimal, educational reconstruction of ERIM's call-gate idea.
 * Stage 0: baseline. Two "compartments" in one process — a trusted secret
 * and untrusted code — with NO protection. The untrusted code reads the
 * secret freely. This is the problem ERIM exists to solve.
 */

//  The "trusted" side: allocates a secret on its own page
static char *make_secret(const char *text) {
  size_t pagesize = sysconf(_SC_PAGESIZE);
  char *page = mmap(NULL, pagesize, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (page == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  strcpy(page, text);
  return page;
}

// The "untrusted" side: code we don't trust, sharing the process

static void untrusted_code(char *secret){
    printf("[untrusted] trying to read the secret...\n");
    printf("[untrusted]: I read:\"%s\"\n",secret );
}

int main(void){
    printf("===minierim - stage 0: baseline, no protection ===\n\n");

    // Trusted side sets up a secret
    char *secret = make_secret("tenant-A private convertaion");
    printf("[trusted] secret is in memory at %p\n\n",(void *)secret);

    // Untrusted code runs in the SAME process and reads it freely
    untrusted_code(secret);

    printf("\n[result] The untrusted code saw the secret. No boundary exists. \n");
    return 0;
}