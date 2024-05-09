/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica6;

import flauta.*;
import Relleno.*;
import Utensilios.*;
/**
 *
 * @author jhona
 */
public class Practica6 {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Tortilla tortillauno = new Tortilla();
        Tortilla tortillados = new Tortilla();
        Tortilla tortillatres = new Tortilla();
        Palillo palillouno = new Palillo("madera");
        Palillo palillodos = new Palillo("madera");
        Palillo palillotres  = new Palillo("madera");
        Aceite aceite = new Aceite("vegetal","frio");
        Queso queso = new Queso("manchego","entero");
        Crema crema = new Crema("acida");
        CarneDeRes carneDeRes = new CarneDeRes();
        Cebolla cebolla = new Cebolla("morada","entera");
        Ajo ajo = new Ajo("entero");
        Hoja_laurel hojaLaurel = new Hoja_laurel();
        Agua agua = new Agua();
        Sal sal = new Sal("grano");
        Pollo pollo = new Pollo();
        Papa papa = new Papa();
        Lechuga lechuga = new Lechuga("romana","entera");
        Tomate tomate = new Tomate();
        Aguacate aguacate = new Aguacate("hass","entero");
        Cilantro cilantro = new Cilantro();
        Olla olla = new Olla("aluminio");
        Comal comal = new Comal("hierro");
        Sarten sarten = new Sarten("hierro");
        Cuchillo cuchillo = new Cuchillo("metal");
        Pelador pelador = new Pelador("plastico");

        Salsa salsauno = new Salsa("guacamole");
        Salsa salsados = new Salsa("morita");
        Salsa salsatres = new Salsa("roja");
        Plato plato = new Plato("ceramica","circular");
        Servilleta servilleta=new Servilleta("papel");
        
        //preparando rellenos
        cuchillo.picar(cebolla);
        cuchillo.picar(tomate);      
        
        //RELLENO DE PAPA
        pelador.pelar(papa);
        cuchillo.picar(papa);
        olla.cocinar(papa, agua, sal);
        papa.escurrir();
        papa.macerar();
        Relleno rellenopapa=new Relleno(papa);
        //RELLENO DE CARNE
        olla.cocinar(carneDeRes, agua, sal, ajo, hojaLaurel, cebolla);
        carneDeRes.enfriar();
        carneDeRes.deshebrar();
        Relleno rellenores=new Relleno(carneDeRes);
        //RELLENO DE POLLO
        olla.cocinar(pollo, agua, sal, ajo, hojaLaurel);
        pollo.enfriar();
        pollo.deshebrar();
        Relleno rellenopollo=new Relleno(pollo);
        
        //CREANDO LOS TACOS
        comal.calentar(tortillauno);
        comal.calentar(tortillados);
        comal.calentar(tortillatres);
        
        
        Flauta flautauno = new Flauta();
        Flauta flautados = new Flauta();
        Flauta flautatres = new Flauta();        
        flautauno.rellenar(rellenopapa, tortillauno);
        flautados.rellenar(rellenores, tortillados);
        flautatres.rellenar(rellenopollo, tortillatres);
        
        sarten.calentar(aceite);
        
        flautauno.enrollar();
        flautauno.asegurar(palillouno);
        flautados.enrollar();
        flautados.asegurar(palillodos);
        flautatres.enrollar();
        flautatres.asegurar(palillotres);
        
        
        sarten.freir(flautauno);
        servilleta.colocar(flautauno);
        sarten.freir(flautados);
        servilleta.colocar(flautados);
        sarten.freir(flautatres);
        servilleta.colocar(flautatres);

        plato.servir(flautauno);
        plato.servir(flautados);
        plato.servir(flautatres);
        
        
        flautauno.poner(tomate,aguacate);
        flautados.esparcir(cilantro, queso, lechuga);
        flautatres.esparcir(cilantro, queso, lechuga);
        flautauno.cubrir(salsauno, crema);
        flautados.cubrir(salsados, crema);
        flautatres.cubrir(salsatres, crema);
        
        
        cuchillo.picar(aguacate);
        cuchillo.picar(cilantro);
        cuchillo.picar(tomate);
        cuchillo.picar(lechuga);
        


        System.out.println("\nLISTO AHORA PUEDES DISFRUTAR DE TUS TRES FLAUTA ");
        System.out.println(flautauno.to_string());;
        System.out.println(flautados.to_string());
        System.out.println(flautatres.to_string());
    }
    
}
