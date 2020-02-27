import sys

# Exercice 4
"""
chaine1 = raw_input("chaine 1 : ")
chaine2 = raw_input("chaine 2 : ")

count = chaine1.count(chaine2)

print "il y a", count , "chaine2 dans chaine1"

if(chaine2 in chaine1):
	print "chaine2 est dans chaine1"
else:
	print "chaine2 n est pas dans chaine1"
"""

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice 5
"""
number = input("indiquer un number : ")

if(number % 2):
	print "number impaire"
else:
	print "number paire"
"""

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice 6
"""
number = input("indiquer un number : ")

if(number > 0):
	print "number positif"
elif(number < 0):
	print "number negatif"
else:
	print "number egale a 0"
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice 7
"""
chaine = raw_input("chaine : ")
number_extract1 = input("number d extraction au debut : ")
number_extract2 = input("number d extraction a la fin: ")


res_chaine1 = chaine[:number_extract1]
res_chaine2 = chaine[len(chaine) - number_extract2:]

print "debut de chaine ", res_chaine1
print "fin de chaine ", res_chaine2
"""
"""
chaine = raw_input("chaine : ")
choise = input("0 : debut\n1 : fin\n->")
number = input("number : ")

if(choise):
	res_chaine = chaine[len(chaine) - number:]
	print "fin de chaine ", res_chaine
else:
	res_chaine = chaine[:number]
	print "debut de chaine ", res_chaine
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 1
"""
chaine = raw_input("chaine : ")

for x in xrange(0,len(chaine)):
	print chaine[x]
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 2
"""
chaine = raw_input("chaine : ")

for x in xrange(0,len(chaine)):
	print chaine[x], x
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 3
"""
chaine = raw_input("chaine : ")
count = 0
for x in xrange(0,len(chaine)):
	if(chaine[x] == 'M' or chaine[x] == 'C'):
		count = count + 1;
print "Acide amines soufre =", count
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 4
"""
chaine = raw_input("chaine : ")

count_A = 0
count_C = 0
count_G = 0
count_T = 0

for x in xrange(0,len(chaine)):
	if(chaine[x] == 'A'):
		count_A = count_A + 1;
	elif(chaine[x] == 'C'):
		count_C = count_C + 1;
	elif(chaine[x] == 'G'):
		count_G = count_G + 1;
	elif(chaine[x] == 'T'):
		count_T = count_T + 1;

print "A :", (1.0*count_A)/len(chaine)*100, "%"
print "C :", (1.0*count_C)/len(chaine)*100, "%"
print "G :", (1.0*count_G)/len(chaine)*100, "%"
print "T :", (1.0*count_T)/len(chaine)*100, "%"
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 5
"""
chaine = raw_input("chaine : ")

buffer = ""

for x in xrange(0,len(chaine)):
	if(chaine[x] == 'T'):
		buffer += 'U'
	else:
		buffer += chaine[x]

print buffer
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 6
"""
chaine = raw_input("chaine : ")

transcription = ""

dico = {"A" : "T", "C" : "G", "G" : "C", "T" : "A"}

for x in range(len(chaine) - 1, -1, -1):
	transcription += dico[chaine[x]]

print transcription
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 7
"""
chaine = raw_input("chaine : ")
count_error = 0
verif = "ACGT"

for x in xrange(0,len(chaine)):
	if(not(chaine[x] in verif)):
		count_error += 1
		print "position :", x

print "nombre d erreur", count_error
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 8
"""
chaine = raw_input("chaine : ")

verif = "ACGT"
i = 0
while(i < len(chaine)):
	if(not(chaine[i] in verif)):
		print "error position", i
		i = len(chaine)
	i += 1
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice bonus 9

chaine = raw_input("chaine : ")

if(len(chaine) % 2):
	print "marche po"
	sys.exit()

test = "AT TA CG GC"

for i in xrange(0,len(chaine) / 2):
	if(chaine[i] + chaine[-i - 1] not in test):
		print "marche po"
		sys.exit()

print "ca marche maguele"