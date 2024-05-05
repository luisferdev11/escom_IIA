
package herencia;

import multiple.Becario;
import simple.Persona;
import simple.SerHumano;

/**
 *
 * @author Saul
 */
public class Herencia {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        SerHumano humano = new SerHumano("Femenino", 3.300, 41.7);
        System.out.println(humano);
        SerHumano samuel = new SerHumano();
        System.out.println(samuel);
        System.out.println(samuel.equals(humano));
        samuel.setSerHumano("Masculino", 4.5, 55.4);
        System.out.println(samuel);
        
        Persona alguien = new Persona();
        System.out.println(alguien);
        Persona laura = new Persona("Femenino", 3.4, 44.8, 
                "Laura Gomez Palacios", 4);
        System.out.println(laura);
        System.out.println(laura.equals(alguien));
        alguien.setPersona("Masculino", 3.95, 48.7, "Genaro Moreno Velez", 5);
        System.out.println(alguien);
        
        humano.respirar();
        samuel.respirar();
        
        alguien.respirar();
        alguien.respirar("agitado");
        alguien.comer();
        
        laura.respirar();
        laura.respirar("nervioso");
        laura.comer();
        
        
        humano.destruir();
        samuel.destruir();
        alguien.destruir();
        laura.destruir();
        humano = null;
        samuel = null;
        alguien = null;
        laura = null;
        System.gc();
        
        
        Becario rocio = new Becario("Femenino", 3.56, 45.0, 
                                    "Rocio Vazquez Perez", 18,
                                    "202412340",
                                    5890.12);
        System.out.println(rocio);
        rocio.respirar();
        rocio.comer("Chilaquiles", "ESCOM");
        rocio.estudiar("Paradigmas");
        rocio.trabajar();
        System.out.println(rocio.cobrar());
        rocio.trabajar(2);
        System.out.println(rocio.cobrar());
    }
    
}
