def lecture_file(filename):
	file = open(filename, "r")
	seq = file.read()
	seq = seq.replace("\n", "")
	file.close()
	return seq


def lecture_file_tabl(filename):
	file = open(filename, "r")
	seqs = file.read().split()
	file.close()
	return seqs


def exo_1():
	codon = raw_input("codon : ")
	seq = lecture_file("txt.style")
	file = open("occurence.style", "w")
	for i in xrange(0, len(seq)):
		if seq[i:i + len(codon)] == codon:
			file.write(str(i + 1) + "\n")
	file.close()


def exo_2():
	seqs = lecture_file_tabl("txt.style")
	buf = 0.0
	for i in xrange(0, len(seqs)):
		buf += len(seqs[i])
	buf /= (len(seqs))
	print buf



#exo_1()
exo_2()