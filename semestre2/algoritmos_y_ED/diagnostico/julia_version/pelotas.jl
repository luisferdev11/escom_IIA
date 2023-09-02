mutable struct Pelota
    alto::Int
    ancho::Int
    color::String
end

function crearPelota(pelotas)
    println("Alto: ")
    alto = parse(Int, readline())
    println("Ancho: ")
    ancho = parse(Int, readline())
    println("Color: ")
    color = readline()
    nueva_pelota = Pelota(alto, ancho, color)
    push!(pelotas, nueva_pelota)
end

function destruirPelota(pelotas)
    println("Índice de la pelota a destruir: ")
    indice = parse(Int, readline())
    if indice < 1 || indice > length(pelotas)
        println("Índice no válido.")
        return
    end
    deleteat!(pelotas, indice)
end

function leerPelotas(pelotas)
    for (i, pelota) in enumerate(pelotas)
        println("Pelota ", i)
        println("Alto: ", pelota.alto)
        println("Ancho: ", pelota.ancho)
        println("Color: ", pelota.color)
    end
end

function menuOperaciones()
    pelotas = []
    while true
        println("1. Crear pelota")
        println("2. Destruir pelota")
        println("3. Leer pelotas")
        println("4. Salir")
        println("Opción: ")
        opcion = parse(Int, readline())
        
        if opcion == 1
            crearPelota(pelotas)
        elseif opcion == 2
            destruirPelota(pelotas)
        elseif opcion == 3
            leerPelotas(pelotas)
        elseif opcion == 4
            println("Saliendo...")
            break
        else
            println("Opción inválida.")
        end
    end
end

menuOperaciones()
