import matplotlib.pyplot as plt


def lecture_id(line):
	identity = ""
	index = 0
	char = "A"
	while char != "|":
		char = line[index]
		index += 1
	char = line[index]
	while char != "|":
		char = line[index]
		if char != "|":
			identity += char
		index += 1
	return identity

def lecture_file(filename):
    file = open(filename, "r")
    bufferString = file.readline()
    seq = ["", ""]
    seq[0] = lecture_id(bufferString)
    bufferString = file.readline()
    while bufferString :
    	seq[1] = seq[1] + bufferString[0 : len(bufferString)]
    	bufferString = file.readline()
    file.close()
    seq[1] = seq[1].replace('\n', '')
    return seq


def init_save(sequence1, sequence2):
	save = []
	for i in range(0, len(sequence2[1]) + 1):
		save.append([])
		for j in range(0, len(sequence1[1]) + 1):
			save[i].append(' ')

	for i in range(1, len(save)):
		save[i][0] = sequence2[1][i - 1]

	for i in range(1, len(save[0])):
		save[0][i] = sequence1[1][i - 1]
	return save


def write_save(save, filename):
	file = open(filename, "w")
	for i in range(len(save) - 1, -1, -1):
		for j in range (0, len(save[i])):
			file.write(save[i][j])
		file.write("\n")
	file.close()


def draw_point(i, j, pat):
	for k in range(0, pat):
		if i == j:
			plt.scatter(i + k, j + k, c = "red", s=10)
		else:
			plt.scatter(i + k, j + k, c = "black", s=10)


def write_point(save, i, j, pat):
	for k in range(1, pat + 1):
		save[j + k][i + k] = 'X'


def valid_segment(seq1, seq2, pat, identity):
	count = 0.0
	if len(seq1) != pat or len(seq2) != pat:
		return
	for k in range(0, pat):
		if seq1[k] == seq2[k]:
			count += 1
	if count >= ((identity / 100.0) * pat):
		return True
	return False


def caclulate_point(sequence1, sequence2, identity, pat, save):
	for i in range(0, len(sequence1), pat):
		for j in range(0, len(sequence2), pat):
			if valid_segment(sequence1[i : i + pat], sequence2[j : j + pat], pat, identity):
				draw_point(i, j, pat)
				write_point(save, i, j, pat)


file_seq1 = raw_input('sequence 1 : ')
file_seq2 = raw_input('sequence 2 : ')
fenetre = input('taille d une fenetre : ')
identity_min = input('seuil d identite minimal : ')
output_file = raw_input('fichier de sorti : ')


sequence1 = lecture_file(file_seq1)
sequence2 = lecture_file(file_seq2)
save_plot = init_save(sequence1, sequence2)	

plt.title("My Dot Plot")
plt.xlabel(sequence1[0])
plt.ylabel(sequence2[0])
plt.xlim(0, len(sequence1[1]))
plt.ylim(0, len(sequence2[1]))

caclulate_point(sequence1[1], sequence2[1], identity_min, fenetre, save_plot)

write_save(save_plot, output_file + ".txt")

plt.savefig(output_file)
plt.show()

plt.close()