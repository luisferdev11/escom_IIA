/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.vehiculos;
import com.mycompany.vehiculos.Transporte;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public class UpCasting {
    public void hacerUpCasting(Transporte transporte) {
        transporte.mover();
    }

    public void realizarUpCasting(Transporte[] transportes) {
        for (Transporte t : transportes) {
            hacerUpCasting(t);
        }
    }
}

