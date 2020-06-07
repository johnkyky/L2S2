BATTISTON Ugo 21805659
JAM Mathys 21801747

Afin de construire l'arbre de dérivation d'une expression régulière, nous avons fait le choix de rajouter une structure de donnée PILEADERIV, une pile contenant des adresses d'ADERIV. 
L'algo est le même que l'algo de "reconnaissance d'un mot", mais on utilise une pile de PILEADERIV en plus. Lors que l'on empile une recette, dans l'arbre, ça devient une feuille. Afin d'y accéder facilement, on empile dans la pile l'adresse de la feuille afin de pouvoir accéder à l'élément sans parcourir l'abre. 
La pile PILEADERIV a pour sommet l'adresse de l'élément non terminanx le plus au dans la pile de transition. Lors que la pile de transition est vide, la pile de PILEADERIV l'est aussi.
Cela nous permet d'éviter de faire une fonction récursive.