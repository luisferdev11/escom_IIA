/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */

package com.mycompany.sensacion_termica;
import com.mycompany.sensacion_termica.CalcularSensacion;

/**
 *
 * @author escom
 */
public class Sensacion_termica {
    
    
    
    public static void main(String[] args) {
        CalcularSensacion miSensacion = new CalcularSensacion() {
            @Override
            public double calculaSensacion(double v, double t) {
                // imprime 12345 si no es valido
                if(t <= 10){
                    return 12345;
                }
                return (13.12 + 0.6215 * t - 11.37 * Math.pow(v, 0.16) + 0.3965 * t * Math.pow(v, 0.16));
            }
        };
        
        //double sensacion = miSensacion.calculaSensacion(20, 10);
        
        double sensacion = miSensacion.calculaSensacion(20, 20);
        
        System.out.println("El indice de sensacion termica es de, en caso de no ser valido mostraremos 12345: " + sensacion);
    }
}


//  public double calculaSensacion(double v, double t) {
 //               return (t <= 10) ? 13.12 + 0.6215 * t - 11.37 * Math.pow(v, 0.16) + 0.3965 * t * Math.pow(v, 0.16) : Double.NaN;
  //          };