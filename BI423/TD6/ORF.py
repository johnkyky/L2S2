def lecture_file(filename):
	file = open(filename, "r")
	seq = file.read().split()
	file.close()
	return seq[0]



def inverse_complementaire(sequence):
	dico = {"A" : "T", "T" : "A", "C" : "G", "G" : "C"}		
	return "".join([dico[sequence[-i - 1]] for i in range(0, len(sequence) - 1)])



def find(start, end, pat, search, sequence):
	for i in range(start, end, pat):
		for j in xrange(0, len(search)):
			if seq[i:i + len(search[j])] == search[j]:
				return i + 1
	return -1


def find_CDS(sequence, count_cds, sens, min_nucleo):
	codon_start = ["ATG"]
	codon_stop = ["TAA", "TAG", "TGA"]

	deb = 0

	while(deb < len(sequence) - 2):
		debut = find(deb, len(sequence), 1, codon_start, sequence)
		if(debut == -1):
			break;

		deb = debut;
		cadre = ((debut - 1) % 3) + 1
		fin = find(debut + 2, len(sequence), 3, codon_stop, sequence) + 2
		if(fin == -1 or fin < debut):
			break;

		nt = fin - debut + 1
		codon = nt / 3
		aa = codon - 1

		cadre *= sens
		if(nt >= min_nucleo):
			count_cds += 1
			print count_cds, "\t", cadre, "\t", debut, "\t", fin, "\t", nt, "\t", codon, "\t", aa

	return count_cds




file = raw_input("Fichier a analyser : ")
min_nucleotide = input("Minimum de nucleotide : ")
seq = lecture_file(file)
print "sequence : ", seq
print "\nCDS\tCadre\tDebut\tFin\tNT\tCodon\tAA"

nbr_cds = 0

nbr_cds = find_CDS(seq, nbr_cds, 1, min_nucleotide)
seq = inverse_complementaire(seq)
nbr_cds = find_CDS(seq, nbr_cds, -1, min_nucleotide)