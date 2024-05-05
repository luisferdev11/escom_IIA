/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package multiple;

/**
 *
 * @author Saul
 */
public interface Trabajador {
    double SUELDO_BASE_BECARIO = 6000.0;
    double HORA_TRABAJADA = 60.0;
    double cobrar();
    void trabajar();
    void trabajar(int horasExtra);
}
