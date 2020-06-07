L'archive BATTISTON_Ugo.tar contient les fichiers :
- Le fichier README.md que vous êtes en train de lire.
- Mainclass.java CmdAddGroupe.java CmdCercle.java CmdExit.java CmdGroupe.java CmdHelp.java CmdMove.java CmdPrint.java CmdRectangle.java CmdRemoveGroupe.java CmdRemove.java CmdSetPosition.java CmdSetRadius.java CmdSetSize.java Commande.java DrawableApp.java Drawable.java DrawableUI.java Rectangle.java Transformable.java fichiers sources du programme.
- Le fichier makefile permetant la compilation grâce à la commande "make", le fichier de config "data" est a mettre en parametre lors de l'éxécution du programme. La supression des fichiers n'essessaire à l'éxécution du	programme se fait grâce à la commande "make clear".


Une fois le programme lancé, vous disposez d'une liste de commandes. La commande help permet de lister les commandes ainsi que leurs parametres.

print       (nom) ...
	- Afficher un/des objet(s), si nom n'est pas resseigner, elle affiche tous les objets

cercle      [nom] [position x] [position y] [radius]
	- Construit un nouveau cercle avec ces differents parametres

rectangle   [nom] [position x] [position y] [largeur] [hauteur]
	- Construit un nouveau rectangle avec ces differents parametres

setradius   [nom] ... [radius]
	- Modifie le radius du/des cercle(s) de/des nom(s), avec le param radius

setsize     [nom] ... [largeur] [hauteur]
	- Modifie la taille du/des rectangle(s) de/des nom(s), avec le param radius*

setposition [nom] ... [position x] [position y]
	- Modifie la position du/des objet(s) nom avec une nouvelle position

move        [nom] [offset x] [offset y]
	- Deplace la position du/des objet(s) nom avec un decalage

rm          [nom] ...
	- Supprime un/des objet(s)

groupe      [nom] ...
	- Permet la creation de un/des groupe(s) nom

addgroupe   [groupe] [element] ...
	- Permet l'ajout au groupe groupe le/les objet(s) nom

rmgroupe    [groupe] [element] ...
	- Supprime du goupe groupe le/les objet(s) element

help
	- Liste les commandes disponible en indiquant les parametres

exit
	- Quitte le programme


Le therme element permet de decrire une forme rectangle, cercle.
Le therme groupe permet de decrire un groupe.
Le therme nom permet de decrire une forme et un groupe.