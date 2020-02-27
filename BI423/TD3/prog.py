import sys


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice 1
"""
def main():
	file = raw_input("file name : ")
	f = open(file, "r")
	buff = "start"
	line = ""
	while(buff != ""):
		buff = f.readline()
		line = line + buff[:-1] 
	f.close()
	return line
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice 2
"""
def main():
	file = raw_input("file name : ")
	fr = open(file, "r")
	buff = "start"
	line = ""
	while(buff != ""):
		buff = fr.readline()
		line = line + buff[:-1] 
	fr.close()

	fw = open("buffer.style", "w")
	fw.write(str(line.count("AT") * 100 / (len(line) / 2)))
	fw.close()

	return "open buffer.style !"
"""


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


# Exercice 3

def main():
	file = raw_input("file name : ")
	fr = open(file, "r")
	buff = "start"
	line = ""
	while(buff != ""):
		buff = fr.readline()
		line = line + buff
	fr.close()

	line = line.replace('\n', '')
	done = True

	while(done):
		choix = raw_input("trans ou inv_comp ou exit: ")
		buff = ""
		dico = { 'A' : 'T', 'T' : 'A', 'C' : 'G', 'G' : 'C'}

		if(choix == "trans"):
			buff = line
			buff = buff.replace('T', 'U')
		elif(choix == "inv_comp"):
			for i in range(len(line) - 1, -1, -1):
				buff += dico[line[i]]
		elif(choix == "exit"):
			done = False


		fw = open("buffer.style", "w")
		fw.write(buff)
		fw.close()

	return "open buffer.style !"


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""



print main()