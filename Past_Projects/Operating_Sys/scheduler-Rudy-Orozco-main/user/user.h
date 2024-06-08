struct stat;
struct pstat;

#ifndef COLOR_H
#define COLOR_H
#define NPROC 64
enum COLOR { RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET };

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct pstat {
  char name[NPROC][16];        // name of the process
  enum procstate state[NPROC]; // state of the process   
  int inuse[NPROC];            // whether this slot of the process table is in use (1 or 0)
  int tickets[NPROC];          // the number of tickets this process has
  int pid[NPROC];              // the PID of each process
  enum COLOR color[NPROC];     // the color of the proces
  int ticks[NPROC];            // the number of ticks each process has accumulated 
};


#endif



// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int setColor(enum COLOR );
int setTickets(int);
int getpinfo(struct pstat *);
int ps(void);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);
