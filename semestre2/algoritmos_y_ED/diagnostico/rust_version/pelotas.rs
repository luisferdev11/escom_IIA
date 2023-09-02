use std::io;

#[derive(Debug)]
struct Pelota {
    alto: i32,
    ancho: i32,
    color: String,
}

fn main() {
    let mut pelotas: Vec<Pelota> = Vec::new();
    loop {
        println!("1. Crear pelota");
        println!("2. Destruir pelota");
        println!("3. Leer pelotas");
        println!("4. Salir");

        let mut opcion = String::new();
        io::stdin().read_line(&mut opcion).expect("Error al leer la opción");
        let opcion: u8 = match opcion.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        match opcion {
            1 => crear_pelota(&mut pelotas),
            2 => destruir_pelota(&mut pelotas),
            3 => leer_pelotas(&pelotas),
            4 => break,
            _ => println!("Opción no válida"),
        }
    }
}

fn crear_pelota(pelotas: &mut Vec<Pelota>) {
    let mut alto_str = String::new();
    let mut ancho_str = String::new();
    let mut color = String::new();

    println!("Introduce el alto:");
    io::stdin().read_line(&mut alto_str).expect("Error al leer el alto");
    let alto: i32 = match alto_str.trim().parse() {
        Ok(num) => num,
        Err(_) => return,
    };

    println!("Introduce el ancho:");
    io::stdin().read_line(&mut ancho_str).expect("Error al leer el ancho");
    let ancho: i32 = match ancho_str.trim().parse() {
        Ok(num) => num,
        Err(_) => return,
    };

    println!("Introduce el color:");
    io::stdin().read_line(&mut color).expect("Error al leer el color");
    let color = color.trim().to_string();

    let pelota = Pelota { alto, ancho, color };
    pelotas.push(pelota);
}

fn destruir_pelota(pelotas: &mut Vec<Pelota>) {
    let mut index_str = String::new();

    println!("Introduce el índice de la pelota para destruir:");
    io::stdin().read_line(&mut index_str).expect("Error al leer el índice");
    let index: usize = match index_str.trim().parse() {
        Ok(num) => num,
        Err(_) => return,
    };

    if index > 0 && index <= pelotas.len() {
        pelotas.remove(index - 1);
    } else {
        println!("Índice no válido");
    }
}

fn leer_pelotas(pelotas: &[Pelota]) {
    for (i, pelota) in pelotas.iter().enumerate() {
        println!("Pelota {}:", i + 1);
        println!("  Alto: {}", pelota.alto);
        println!("  Ancho: {}", pelota.ancho);
        println!("  Color: {}", pelota.color);
    }
}
