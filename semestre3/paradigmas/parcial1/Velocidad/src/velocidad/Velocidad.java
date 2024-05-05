/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package velocidad;

import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import modelo.Funcion;
import modelo.FuncionPolimorfica;

/**
 *
 * @author Saul
 */
public class Velocidad {
    public static final double VELOCIDAD_CERO = 331.3;
    public static final double COEFICIENTE = 0.61;
    public static double multiplica(double dx, double dy) {
        return dx * dy;    
    }
    public static double suma(double dx, double dy) {
        return dx + dy;    
    }
    public static List<Double> calcularVelocidades(int temperaturaInicial, 
            int temperaturaFinal) {
        List<Double> lista = new LinkedList<>();
        for(int temperatura=temperaturaInicial; 
                temperatura<=temperaturaFinal;
                    temperatura++) {
                double velocidad = suma(VELOCIDAD_CERO, 
                        multiplica(COEFICIENTE, temperatura));
                lista.add(velocidad);
                }
        return lista;
    }
    public static void solicitarTemperaturas(int selector) {
        int temperaturaInicial;
        int temperaturaFinal;
        Scanner teclado = new Scanner(System.in);
        System.out.print(
                "Introduzca temperatura inicial (grados centigrados): ");
        temperaturaInicial = teclado.nextInt();
        System.out.print(
                "Introduzca temperatura final (grados centigrados): ");
        temperaturaFinal = teclado.nextInt();
        List<Double> velocidades = null;
        if(selector==1) {
            velocidades = calcularVelocidades(
                            temperaturaInicial, temperaturaFinal);
            }
        else 
        if(selector==2) {
            velocidades = calcularVelocidadesCompuestas(
                            temperaturaInicial, temperaturaFinal);
            }
        else 
        if(selector==3) {
            velocidades = calcularVelocidadesPolimorficas(
                            temperaturaInicial, temperaturaFinal);
            }
        imprimirLista(velocidades, temperaturaInicial);
        
    }
    public static void imprimirLista(List<Double> lista, int temperaturaInicial) {
        for(Double velocidad: lista) {
            System.out.println("La velocidad del sonido a temperatura " +
                    temperaturaInicial++ + " es " + velocidad + " m/s.");
            }
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        solicitarTemperaturas(1);
        
        solicitarTemperaturas(2);
        
        solicitarTemperaturas(3);
    }
    public static Funcion componer(Funcion funcionUno, Funcion funcionDos) {
        return new Funcion() {
            public double opera(double x, double y) {
                return funcionUno.opera(x, funcionDos.opera(COEFICIENTE, y));
            }
        };
    }
    public static List<Double> calcularVelocidadesCompuestas(int temperaturaInicial, 
            int temperaturaFinal) {
        Funcion multiplica = new Funcion() {
            @Override
            public double opera(double x, double y) {
                return x * y;
            }
        };
        Funcion suma = new Funcion() {
            @Override
            public double opera(double x, double y) {
                return x + y;
            }
        };
        List<Double> lista = new LinkedList<>();
        for(int temperatura=temperaturaInicial; 
                temperatura<=temperaturaFinal;
                    temperatura++) {
                double velocidad = componer(suma, multiplica).opera(
                        VELOCIDAD_CERO, temperatura);
                lista.add(velocidad);
                }
        return lista;
    }
    public static List<Double> calcularVelocidadesPolimorficas(int temperaturaInicial, 
            int temperaturaFinal) {
        FuncionPolimorfica<Double, Double, Double> multiplica = 
                new FuncionPolimorfica<Double, Double, Double>() {
            @Override
            public Double opera(Double x, Double y) {
                return x * y;
            }
        };
        FuncionPolimorfica<Double, Double, Double> suma = 
                new FuncionPolimorfica<Double, Double, Double>() {
            @Override
            public Double opera(Double x, Double y) {
                return x + y;
            }
        };
        List<Double> lista = new LinkedList<>();
        for(int temperatura=temperaturaInicial; 
                temperatura<=temperaturaFinal;
                    temperatura++) {
            Double temperaturaD = (double)temperatura;
                double velocidad = componerPolimorfico(suma, multiplica).opera(
                        VELOCIDAD_CERO, temperaturaD);
                lista.add(velocidad);
                }
        return lista;
    }
    public static FuncionPolimorfica<Double, Double, Double> componerPolimorfico(
            FuncionPolimorfica<Double, Double, Double> funcionUno, 
            FuncionPolimorfica<Double, Double, Double> funcionDos) {
        return new FuncionPolimorfica<Double, Double, Double>() {
            public Double opera(Double x, Double y) {
                return funcionUno.opera(x, funcionDos.opera(COEFICIENTE, y));
            }
        };
    }
}
