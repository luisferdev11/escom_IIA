from PIL import Image

width, height = 100, 100  # Tamaño de la imagen

#creamos una imagen con un circulo y un cuadrado
img = Image.new("RGB", (width, height), "white")
for x in range(width):
    for y in range(height):
        if (x-50)**2 + (y-50)**2 < 40**2:
            img.putpixel((x, y), (255, 0, 0))
        if 30 < x < 70 and 30 < y < 70:
            img.putpixel((x, y), (0, 0, 255))

        

img.save("imagen.bmp", "BMP")
