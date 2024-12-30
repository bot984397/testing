#include <windows.h>
#include <winternl.h>
#include <stdio.h>

typedef NTSTATUS(NTAPI* NtQueryInformationProcess_t) (
   HANDLE           ProcessHandle,
   PROCESSINFOCLASS ProcessInformationClass,
   PVOID            ProcessInformation,
   ULONG            ProcessInformationLength,
   PULONG           ReturnLength
);

typedef struct
{
   union
   {
      struct
      {
         HANDLE DirectoryHandle;
      } Set;
      struct
      {
         ULONG DriveMap;
         UCHAR DriveType[32];
      } Query;
   };
} PROCESS_DEVICEMAP_INFORMATION;

int main(void)
{
   NtQueryInformationProcess_t NtQueryInformationProcess
      = (NtQueryInformationProcess_t)GetProcAddress(LoadLibraryA("ntdll.dll"), "NtQueryInformationProcess");

   PROCESS_DEVICEMAP_INFORMATION out = { 0 };
   NTSTATUS ret = NtQueryInformationProcess((HANDLE)-1, 0x17, &out, 0x24, 0);

   return 0;
}
