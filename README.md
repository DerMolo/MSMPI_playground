# MSMPI_playground
single cpp file containing all my MSMPI tests

Build notes:
*Meant to be run on visual studios with vcpkg. (clone the entire repo within a new visual studio project) 
- installer for [MSMPI](https://www.microsoft.com/en-us/download/details.aspx?id=105289)

Install MSMPI seperately and include the following environment variables: 
  
- MSMPI_BIN: C:\Program Files\Microsoft MPI\Bin\
- MSMPI_INC: C:\Program Files (x86)\Microsoft SDKs\MPI\Include
- MSMPI_LIB64: C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64
- MSMPI_BENCHMARKS: C:\Program Files\Microsoft MPI\Benchmarks\

Configuring Visual Studios to debug via mpiexec: 
Project -> Project properties -> Debugging  
Command: C:\Program Files\Microsoft MPI\Bin\mpiexec.exe  
Command arguments: -n 3 "$(TargetPath)"  
*edit the number of cores used via command argument.    

Type the following visual studio's developer console:  
- vcpkg integrate install
- vcpkg install












