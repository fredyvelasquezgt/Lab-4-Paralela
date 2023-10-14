#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Función para calcular la suma de Riemann en un subintervalo
double calcular_suma_riemann(double a, double b, int num_subintervalos) {
    double delta_x = (b - a) / num_subintervalos;
    double suma_parcial = 0.0;
    for (int i = 0; i < num_subintervalos; i++) {
        double x_i = a + i * delta_x;
        double f_x_i = x_i * x_i;  // Reemplaza con tu función
        suma_parcial += f_x_i * delta_x;
    }
    return suma_parcial;
}

int main() {
    double a = 0.0;
    double b = 1.0;
    int num_subintervalos = 1000000; // Ajustar según sea necesario

    double start_time, end_time;
    
    // Versión secuencial
    start_time = omp_get_wtime();
    double suma_secuencial = calcular_suma_riemann(a, b, num_subintervalos);
    end_time = omp_get_wtime();
    printf("Aproximación de la integral (secuencial): %f\n", suma_secuencial);
    printf("Tiempo de ejecución (secuencial): %f segundos\n", end_time - start_time);

    // Versión paralela con OpenMP
    start_time = omp_get_wtime();
    double suma_paralela = 0.0;
    #pragma omp parallel for reduction(+:suma_paralela)
    for (int i = 0; i < num_subintervalos; i++) {
        double x_i = a + i * (b - a) / num_subintervalos;
        double f_x_i = x_i * x_i;  // Reemplaza con tu función
        suma_paralela += f_x_i * (b - a) / num_subintervalos;
    }
    end_time = omp_get_wtime();
    printf("\nAproximación de la integral (paralela con OpenMP): %f\n", suma_paralela);
    printf("Tiempo de ejecución (paralela con OpenMP): %f segundos\n", end_time - start_time);

    return 0;
}
