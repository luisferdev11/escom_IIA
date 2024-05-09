/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package excepciones;

/**
 *
 * @author Saul
 */
public class DivisionPorCeroException extends ArithmeticException {
    private String mensaje;
    public DivisionPorCeroException() {
        this("Excepcion en la division b no puede valer cero.");
    }
    public DivisionPorCeroException(String mensaje) {
        super(mensaje);
        this.mensaje = mensaje;
    }
    @Override
    public String toString() {
        return mensaje;
    }
}
