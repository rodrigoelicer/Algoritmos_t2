def obtenerContornos(arr):
	if(len(arr) <=1):
		return [(arr[0][0],arr[0][1]),(arr[0][2],0)]
	else:
		c1 = obtenerContornos(arr[0:len(arr)/2])
		c2 = obtenerContornos(arr[len(arr)/2:len(arr)])

		i = j = 0

		print("c1: "+str(c1))
		print("c2: "+str(c2))

		c3 = []

		while(i<len(c1) or j<len(c2)):
			#print("i: "+str(i))
			#print("j: "+str(j))
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
				print("CD")
				if(j == 0):
					print("C")
					c3.append(c1[i])
				elif(c1[i][1] > c2[j-1][1]):
					print("D")
					c3.append(c1[i])
				elif(c1[i][1] < c2[j-1][1] and c1[i-1][1] > c2[j-1][1]):
					c3.append((c1[i][0],c2[j-1][1]))
				i += 1
			#Verifica si la tupla en c2 es menor a la tupla en c1
			elif(c1[i][0] > c2[j][0]):
				print("FG")
				if(i == 0):
					print("F")
					c3.append(c2[j])
				elif(c2[j][1] > c1[i-1][1]):
					print("G")
					c3.append(c2[j])
				elif(c2[j][1] < c1[i-1][1] and c2[j-1][1] > c1[i-1][1]):
					c3.append((c2[j][0],c1[i-1][1]))
				j += 1
			#misma coord x
			else:
				print("IJ")
				if(c1[i][1] > c2[j][1]):
					print("I")
					c3.append(c1[i])
					i += 1
				else:
					print("J")
					c3.append(c2[j])
					j += 1

		print(c3)
		return c3

'''n = int(raw_input("Ingrese cantidad edificios\n"))
m = []
for i in range(n):
	c = raw_input("ingrese coordenadas\n")
	c=map(int,c.split(" "))
	m.append(tuple(c))
'''

m = [(1,3,3),(2,4,4),(5,2,8),(6,5,7),(8,4,9)]
print(obtenerContornos(m))
