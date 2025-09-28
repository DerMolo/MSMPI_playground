# MSMPI_playground
Description:  
solution containing all of my MSMPI tests

Build notes:
*Meant to be run on visual studios with vcpkg. (clone the entire repo as a new project) 
- installer for [MSMPI](https://www.microsoft.com/en-us/download/details.aspx?id=105289)

Install MSMPI seperately and include the following environment variables: 
  
- MSMPI_BIN: C:\Program Files\Microsoft MPI\Bin\
- MSMPI_INC: C:\Program Files (x86)\Microsoft SDKs\MPI\Include
- MSMPI_LIB64: C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64
- MSMPI_BENCHMARKS: C:\Program Files\Microsoft MPI\Benchmarks\

Install vcpkg seperately add/edit the following environment variables [URL to vcpkg installer](https://vcpkg.io/en/).  
- $path: C:\vcpkg  
- VCPKG_ROOT: C:\vcpkg  
  
Debugging the solution via mpiexec.exe:   
Go to: Project -> Project properties -> Debugging  
Command: C:\Program Files\Microsoft MPI\Bin\mpiexec.exe  
Command arguments: -n 3 "$(TargetPath)"  
*edit the number of cores used via command argument.    

Type the following visual studio's developer console:  
- vcpkg integrate install
- vcpkg install

Building with CMAKE:  
In visual studios, open the CMakeLists.txt file.  
Visual studios will automatically build the project once in here.  
Afterwards, simply open msMPITest.cpp.  












