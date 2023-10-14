# Laboratorio 4 - Paralela

## Instrucciones para ejecutar los programas

### Simulación de Integral con MPI

`mpicc -o integral_mpi integral_mpi.c`

`mpiexec -n <número_de_procesos> ./integral_mpi`

### Simulación de Integral con OpenMP

`gcc -fopenmp -o integral_openmp integral_openmp.c`

`./integral_openmp`

### Versión Secuencial y Paralela con OpenMP

`gcc -o secuencial secuencial.c`

`./secuencial`

`gcc -fopenmp -o paralela_openmp paralela_openmp.c`

`./paralela_openmp`




