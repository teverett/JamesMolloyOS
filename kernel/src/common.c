// common.c -- Defines some global functions.
//             From JamesM's kernel development tutorials.

#include "common.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
    u8int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16int inw(u16int port)
{
    u16int ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// Copy len bytes from src to dest.
void memcpy(u8int *dest, const u8int *src, u32int len)
{
    const u8int *sp = (const u8int *)src;
    u8int *dp = (u8int *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

// Write len copies of val into dest.
void memset(u8int *dest, u8int val, u32int len)
{
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

// Bug fix (per OSDev wiki "James Molloy's Tutorial Known Bugs" - Missing
// functions): GCC assumes memcpy, memset, memmove and memcmp are always
// available and can emit implicit calls to them for optimization purposes,
// even from code that never calls them directly. Only memcpy/memset were
// provided; add the other two.

// Copy len bytes from src to dest, correctly handling overlapping regions.
void memmove(u8int *dest, const u8int *src, u32int len)
{
    if (dest < src)
    {
        for (u32int i = 0; i < len; i++)
            dest[i] = src[i];
    }
    else
    {
        for (u32int i = len; i != 0; i--)
            dest[i-1] = src[i-1];
    }
}

// Compare len bytes of s1 and s2. Returns 0 if equal, a negative value if
// s1 < s2, or a positive value if s1 > s2 (as unsigned bytes).
int memcmp(const u8int *s1, const u8int *s2, u32int len)
{
    for ( ; len != 0; len--, s1++, s2++)
    {
        if (*s1 != *s2)
            return (int)*s1 - (int)*s2;
    }
    return 0;
}

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2)
{
      int i = 0;
      int failed = 0;
      while(str1[i] != '\0' && str2[i] != '\0')
      {
          if(str1[i] != str2[i])
          {
              failed = 1;
              break;
          }
          i++;
      }
      // why did the loop exit?
      if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
          failed = 1;
  
      return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src)
{
    char *ret = dest;
    // Bug fix: the old `while (*src != 0)` post-check tested src *after* it
    // had already advanced past the copied byte, so the loop stopped one byte
    // early and never copied the terminating '\0'. Every strcpy'd buffer was
    // left unterminated, causing later strlen/strcmp/strcat calls to read
    // past the intended field into whatever memory followed it. Folding the
    // copy and the terminator check into the loop condition copies the NUL
    // as the final iteration, then stops.
    while ((*dest++ = *src++) != 0)
        ;
    return ret;
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src)
{
    char *ret = dest;
    // Bug fix: `*dest = *dest++;` modified and read `dest` twice between
    // sequence points, which is undefined behaviour in C, so this
    // end-of-string scan didn't reliably advance dest to the '\0'. Just
    // advance the pointer; there's nothing to write until we reach the end.
    while (*dest != 0)
        dest++;

    while ((*dest++ = *src++) != 0)
        ;
    return ret;
}

int strlen(char *src)
{
    int i = 0;
    while (*src++)
        i++;
    return i;
}

extern void panic(const char *message, const char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    monitor_write("PANIC(");
    monitor_write(message);
    monitor_write(") at ");
    monitor_write(file);
    monitor_write(":");
    monitor_write_dec(line);
    monitor_write("\n");
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const char *file, u32int line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    monitor_write("ASSERTION-FAILED(");
    monitor_write(desc);
    monitor_write(") at ");
    monitor_write(file);
    monitor_write(":");
    monitor_write_dec(line);
    monitor_write("\n");
    // Halt by going into an infinite loop.
    for(;;);
}
