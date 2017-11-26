#!/usr/bin/env python
# -*- coding: utf-8 -*-

def obtenerContornos(arr):
	if(len(arr) <=1):
		#Caso base donde transforma 1 3-tupla de 1 edificio en 2 2-tuplas
		#Ej: [(1,3,3)] -> [(1,3),(3,0)]
		return [(arr[0][0],arr[0][1]),(arr[0][2],0)]
	else:
		#Conquistar
		c1 = obtenerContornos(arr[0:len(arr)/2])
		c2 = obtenerContornos(arr[len(arr)/2:len(arr)])

		i = j = 0

		print("c1: "+str(c1))
		print("c2: "+str(c2))

		#arreglo temporal, en C habrá que liberarlo cada vez
		c3 = []

		#Itera hasta que se haya recorrido ambos contornos
		while(i<len(c1) or j<len(c2)):
			#Se acaba el contorno 1
			if(i == len(c1)):
				print("A")
				c3.append(c2[j])
				j += 1
			#Se acaba el contorno 2
			elif(j == len(c2)):
				print("B")
				c3.append(c1[i])
				i += 1
			#Verifica si la tupla en c1 es menor a la tupla en c2
			elif(c1[i][0] < c2[j][0]):
				print("CDE")
				#Si no ha habido un elemento de c2 menor a c1
				if(j == 0):
					print("C")
					c3.append(c1[i])
				#Si la altura en c1 es mayor a la altura previa de c2 (c2[j-1])
				elif(c1[i][1] > c2[j-1][1]):
					print("D")
					c3.append(c1[i])
				#Si la altura de c1[i] es menor a la altura previa de c2[j] (c2[j-1]),
				#PERO al mismo tiempo la altura previa de c1 (c1[i-1]) es mayor
				#a la altura previa de c2 (c2[j-1])
				elif(i!= 0 and c1[i][1] < c2[j-1][1] and c1[i-1][1] > c2[j-1][1]):
					print("E")
					c3.append((c1[i][0],c2[j-1][1]))
				i += 1
			#Verifica si la tupla en c2 es menor a la tupla en c1
			elif(c1[i][0] > c2[j][0]):
				print("FGH")
				#Si no ha habido un elemento de c1 menor a c2
				if(i == 0):
					print("F")
					c3.append(c2[j])
				#Si la altura en c2 es mayor a la altura previa de c1 (c1[i-1])
				elif(c2[j][1] > c1[i-1][1]):
					print("G")
					c3.append(c2[j])
				#Si la altura de c2[j] es menor a la altura previa de c1[i] (c1[i-1]),
				#PERO al mismo tiempo la altura previa de c2 (c2[j-1]) es mayor
				#a la altura previa de c1 (c1[i-1])
				elif(j!= 0 and c2[j][1] < c1[i-1][1] and c2[j-1][1] > c1[i-1][1]):
					print("H")
					c3.append((c2[j][0],c1[i-1][1]))
				j += 1
			#misma coordenada x
			else:
				print("IJKLMN")
				#Ambos contornos inician donde mismo
				if(j==0 and i==0):
					print("IJ")
					if(c1[i][1] > c2[j][1]):
						print("I")
						c3.append(c1[i])
					else:
						print("J")
						c3.append(c2[j])
				#Contorno 2 está en el inicio
				elif(j==0):
					print("K1")
					#Si no hay continuidad (misma altura), se agrega la tupla
					if(c2[j][1] != c1[i-1][1]):
						print("K2")
						c3.append(c2[j])
				#Contorno 1 está en el inicio
				elif(i==0):
					print("L1")
					#Si no hay continuidad (misma altura), se agrega la tupla
					if(c1[i][1] != c2[j-1][1]):
						print("L2")
						c3.append(c1[i])
				#Si no hay continuidad (misma altura), se agrega la tupla
				elif(c2[j][1] != c1[i-1][1]):
					print("M")
					c3.append(c2[j])
				#Si no hay continuidad (misma altura), se agrega la tupla
				elif(c1[i][1] != c2[j-1][1]):
					print("N")
					c3.append(c1[i])

				j += 1
				i += 1

		print(c3)
		return c3

def colision(contorno,dron):
	if(list(dron)[1] == 0):
		return True
	if (len(contorno) == 0):
		return False
	else:
		medio = len(contorno)/2
		print "Mitad contorno X: "+ str(contorno[medio][0])
		print "Dron X: "+ str(list(dron)[0])
		#Cae justo en una coordenada del contorno
		if (contorno[medio][0] == list(dron)[0]):
			print("12")
			#Si la altura es mayor
			if(contorno[medio][1] >= list(dron)[1]):
				print("1")
				return True
			#Si la altura es menor, no necesariamente significa que no vaya
			#a chocar. Puede darse el caso donde se termina un edificio. Habrá
			#que verificar que la altura de la coord anterior también es mayor
			else:
				print("2")
				if(contorno[medio-1][1] >= list(dron)[1]):
					print("2.1")
					return True
				#El dron está más alto que la coordenada y la coord anterior.
				else:
					return False
		#Verifica cuando el dron está entre medio de 2 coordenadas
		elif( contorno[medio][0] > list(dron)[0] and contorno[medio-1][0] <= list(dron)[0]):
			print("34")
			#contorno es más alto, por lo que choca
			if(contorno[medio-1][1] >= list(dron)[1]):
				print("3")
				return True
			#no choca
			else:
				print("4")
				return False
		#recursividad, sigue buscando
		else:
			if (list(dron)[0] < contorno[medio][0]):
				print("5: "+str(contorno[0:medio]))
				return colision(contorno[0:medio],dron)
			else:
				print("6: "+str(contorno[medio+1:]))
				return colision(contorno[medio+1:],dron)


n = int(raw_input("Ingrese cantidad edificios\n"))
m = []
for i in range(n):
	c = raw_input("ingrese coordenadas\n")
	c = map(int,c.split(" "))
	m.append(tuple(c))

u = obtenerContornos(m)
print(u)

t = int(raw_input("Ingrese cantidad drones\n"))
for i in range(t):
	w = raw_input("ingrese coordenadas drones\n")
	w = map(int,w.split(" "))
	print( colision(u,tuple(w)) )

# 5
# [(1,3,3),(2,4,4),(5,2,8),(6,5,7),(8,4,9)]
# [(1,3),(2,4),(4,0),(5,2),(6,5),(7,2),(8,4),(9,0)]
# 3
# (4,2), (1,7), (2,1)
# true, false, true
