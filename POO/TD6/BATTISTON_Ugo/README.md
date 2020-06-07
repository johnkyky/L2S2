L'archive BATTISTON_Ugo.tar contient les fichiers :
- Le fichier README.md que vous êtes en train de lire.
- Mainclass.java AdresseIP.java CmdExit.java CmdFindDomaine.java CmdFindIP.java CmdFindName.java CmdHelp.java Commande.java DnsApp.java DnsItem.java DNS.java DnsTUI.java NomMachine.java fichiers sources du programme.
- le fichier data qui contient les adresses ip et les noms des machines.
- Le fichier makefile permetant la compilation grâce à la commande "make", le fichier de config "data" est a mettre en parametre lors de l'éxécution du programme. La supression des fichiers n'essessaire à l'éxécution du	programme se fait grâce à la commande "make clear".


Une fois le programme lancé, vous disposez d'une liste de commandes, 
- help
	Affiche la liste des commandes
- exit
	Quitter le programme
- searchIP |ip adress|
	Affiche le nom machine de l'adresse ip mis en parametre
- searchName |machine name|
	Affiche l'ip du nom machine mis en parametre
- ls [-a] |domaine|
	Affiche la liste des noms machines qui appartiennent au domaine mis en parametre si l'option -a est ajouté, la liste serra les ip et non les noms machines
