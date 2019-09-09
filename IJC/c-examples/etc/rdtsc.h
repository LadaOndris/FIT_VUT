/*
 *  rdtsc.h
 *  -----------------------------------------------------------------
 *
 *  function for reading 64 bit timer (Pentium, K6, etc.) 
 *  for GNU C/C++ only 
 *  
 */
#ifndef __GNUC__
#error "use GNU C, please"
#endif

__inline long long rdtsc(void)
{
    register long long edxeax;
    __asm __volatile__ ( "rdtsc" : "=A" (edxeax) ); // compiler-dependent
    return edxeax; 
}

