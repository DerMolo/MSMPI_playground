# MSMPI_playground
single cpp file containing all my MSMPI tests

Build notes:
*Meant to be run on visual studios with vcpkg. (clone the entire repo within a new visual studio project) 
- installer for [MSMPI](https://www.microsoft.com/en-us/download/details.aspx?id=105289)

Install MSMPI seperately and include the following environment variables: 
  
MSMPI_BIN: C:\Program Files\Microsoft MPI\Bin\
MSMPI_INC: C:\Program Files (x86)\Microsoft SDKs\MPI\Include
MSMPI_LIB64: C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64
MSMPI_BENCHMARKS: C:\Program Files\Microsoft MPI\Benchmarks\ 
$path: C:\vcpkg 

Type the following visual studio's developer console: 

- vcpkg integrate install
- vcpkg install msmpi:x64-windows










