#ifndef ADVENT_2025_C17_STRICT_H
#define ADVENT_2025_C17_STRICT_H

/*
   Enforce strict ISO C17

   Ths is mainly needed by MSYS2:
       - Headers enable POSIX/GNU extensions by default.
       - These undefs prevent exposure of non‑standard functions like strdup,
         getline, strndup, asprintf, strtok_r, etc.

   Include before any system headers
*/

#undef _GNU_SOURCE
#undef _POSIX_SOURCE
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#undef __USE_MINGW_ANSI_STDIO
#undef __USE_MINGW_STRINGS

#endif //ADVENT_2025_C17_STRICT_H