def obtenerContornosIniciales(arr):
	if(len(arr) <=1):
		return [(arr[0][0],arr[0][1]),(arr[0][2],0)]
	else:
		c1 = obtenerContornosIniciales(arr[0:len(arr)/2])
		c2 = obtenerContornosIniciales(arr[len(arr)/2:len(arr)])

		i = j = 0

		c3 = []

		#Separados
		if(c1[-1][0] < c2[0][0]):
			return c1+c2
		#Separados
		elif(c2[-1][0] < c1[0][0]):
			return c2+c1

		#Pegados juntitos bien rico
		elif(c1[-1][0] == c2[0][0]):
			c3.append(c1[0:-1])
			#Obtiene tupla intermedia
			if(c1[-1][1] > c2[0][1]):
				temp =(c1[-1][0],c1[-1][1])
			else:
				temp = (c2[0][0],c2[0][1])
			#Verifica si la tupla intermedia tiene la misma altura con la que
			#se venía
			if(temp[1] != c1[-2][1]):
				c3.append(temp)
			c3.append(c2[1:])
			return c3
		#Pegados juntitos bien rico
		elif(c2[-1][0] == c1[0][0]):
			c3.append(c2[0:-1])
			#Obtiene tupla intermedia
			if(c2[-1][1] > c1[0][1]):
				c3.append((c2[-1][0],c2[-1][1]))
			else:
				c3.append((c1[0][0],c1[0][1]))
			#Verifica si la tupla intermedia tiene la misma altura con la que
			#se venía
			if(temp[1] != c2[-2][1]):
				c3.append(temp)
			c3.append(c1[1:])

		#while(i<len(c1) and j<len(c2)):
		#	pass

		return c3

n = int(raw_input("Ingrese cantidad edificios\n"))
m = []
for i in range(n):
	c = raw_input("ingrese coordenadas\n")
	c=map(int,c.split(" "))
	m.append(tuple(c))

print(obtenerContornosIniciales(m))
