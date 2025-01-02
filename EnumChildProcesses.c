#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

#define PPID 0x0

int main (void)
{
   HANDLE hSnap = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
   if (hSnap == INVALID_HANDLE_VALUE)
   {
      return 1;
   }

   PROCESSENTRY32W e;
   e.dwSize = sizeof (PROCESSENTRY32W);
   if (!Process32First (hSnap, &pe)) return 1; do
   {
      if (e.th32ParentProcessID == PPID)
      {
         printf ("child proc: %d\n", e.th32ParentProcessID);
      }
   } while (Process32Next (hSnap, &pe));
}
