#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Función para calcular la suma de Riemann en un subintervalo
double calcular_suma_riemann(double a, double b, int num_subintervalos) {
    double delta_x = (b - a) / num_subintervalos;
    double suma_parcial = 0.0;
    for (int i = 0; i < num_subintervalos; i++) {
        double x_i = a + i * delta_x;
        double f_x_i = funcion_a_evaluar(x_i);  // Reemplace con su función
        suma_parcial += f_x_i * delta_x;
    }
    return suma_parcial;
}

// Función que define la función a integrar (reemplace con su función)
double funcion_a_evaluar(double x) {
    return x * x;  // Reemplace con su función
}

int main(int argc, char *argv[]) {
    int rank, size;
    double a = 0.0;
    double b = 1.0;
    int num_subintervalos = 1000000;  // Ajustar según sea necesario
    double local_a, local_b, suma_parcial_local, suma_total;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Distribuir el trabajo entre los procesos
    int local_num_subintervalos = num_subintervalos / size;
    local_a = a + rank * local_num_subintervalos * (b - a) / num_subintervalos;
    local_b = local_a + local_num_subintervalos * (b - a) / num_subintervalos;

    // Calcular la suma de Riemann local
    suma_parcial_local = calcular_suma_riemann(local_a, local_b, local_num_subintervalos);

    // Recopilar todas las sumas parciales en el proceso maestro
    MPI_Reduce(&suma_parcial_local, &suma_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Proceso maestro imprime el resultado y detalles de los procesos
    if (rank == 0) {
        printf("Número total de procesos: %d\n", size);
        printf("Aproximación de la integral: %f\n", suma_total);
    } else {
        printf("Proceso %d calculó la suma en el intervalo [%f, %f]\n", rank, local_a, local_b);
    }

    MPI_Finalize();
    return 0;
}
