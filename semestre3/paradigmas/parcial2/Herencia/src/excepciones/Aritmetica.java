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
public class Aritmetica {
    public int dividir(int a, int b) throws ArithmeticException {
        int c = 0;
        if(b==0) {
            throw new DivisionPorCeroException();//"Division por cero");
            }
        //try {
            c = a / b;
//        } catch(ArithmeticException e) {
//            e.printStackTrace();
//        } catch(Exception e) {
//            e.printStackTrace();
//        }
//        finally {
//            System.out.println("Pasando por finally antes de regresar");
//            }
        return c;
    }
}
