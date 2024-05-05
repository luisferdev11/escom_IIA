class SerHumano(object):
	genero = ""
	peso = 0.0
	talla = 0.0

	def __init__(self,*args):
		if len(args)==0:
			self.genero = ""
			self.peso = 0.0
			self.talla = 0.0
		else:
			if len(args)==3:
				self.genero = args[0]
				self.peso = float(args[1])
				self.talla = float(args[2])

	def respirar(self):
		print("Respirando")

	def toString(self):
		return "Genero: " + self.genero + "\nPeso  : " + str(self.peso) + "\nTalla : " + str(self.talla)

class Persona(SerHumano):
	nombre = ""
	edad = 0

	def __init__(self,*args):
		if len(args)==0:
			super().__init__()
			self.nombre = ""
			self.edad = 0
		else:
			if len(args)==5:
				super().__init__(args[0], args[1], args[2])
				self.nombre = args[3]
				self.edad = int(args[4])

	def respirar(self, estado):
		super().respirar();
		if estado=="Agitado":
			print("ahg, agh, agh\n")
		else:
			if estado=="Nervioso":
				print("ahg, ahg, ahg, ahg, ahg, ahg\n")
			else:
				if estado=="Tranquilo":
					print(" ... \n")

	def comer(self):
		print("nam, anm, nam\n")

	def toString(self):
		return super().toString() + "\nNombre: " + self.nombre + "\n" + "Edad  : " + str(self.edad) + "\n"


luisa = Persona()

print(luisa.toString())
luisa.respirar("")
luisa.respirar("Tranquilo")
luisa.comer()