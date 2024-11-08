# Philosophers
I never thought philosophy would be so deadly

## Testeur :

```
https://github.com/Rz-Rz/thales_tester.git
```

## Step 1 : comprehension du sujet

L'idee est de pouvoir faire vivre nb_philo philosophes selon une routine bien precise (1-manger / 2-dormir / 3-penser) qui doit durer au maximum time_to_die millisecondes. 

Pour ce faire, un plat de spaghettis est dispose au centre de la table mais chaque philosphe dispose d'une seule fourchette. Etant donne que pour se servir dans un tel plat, il est necessaire d'avoir une 2eme fourchette, on considere que les philosophes mangent lorsqu'ils ont reussi a acceder a leur fourchette (a leur droite) et a celle de leur voisin de gauche. 

De fait, ils ne peuvet pas manger tous en meme temps. 

On peut dors et deja determiner les cas dans lesquels les philosphes vont mourir :

- s'il n'y a qu'un seul philosophe (car une seul fourchette a sa dispo)

ex : ./philo 1 800 200 100

| time | philos |
|-----|----|
| 0 | 1 has taken a fork |
| 800 | 1 died |

- s'il y a nb pair de philo ET que time_to_die / 2 < time_to_eat

ex : ./philo 2 300 200 100

| time | philos |
|-----|----|
| 0 | 1 has taken a fork |
| 0 | 1 has taken a fork |
| 0 | 1 is eating |
| 200 | 1 is sleeping |
| 200 | 2 has taken a fork |
| 200 | 2 has taken a fork |
| 200 | 2 is eating |
| 300 | 1 is thinking |
| 310 | 2 died |

- s'il y a nb impair de philo ET que time_to_die / 3 < time_to_eat

ex : ./philo 3 800 300 100

| time | philos |
|-----|----|
| 0 | 1 has taken a fork |
| 0 | 1 has taken a fork |
| 0 | 1 is eating |
| 300 | 1 is sleeping |
| 300 | 2 has taken a fork |
| 300 | 2 has taken a fork |
| 300 | 2 is eating |
| 400 | 1 is thinking |
| 600 | 2 is sleeping |
| 600 | 3 has taken a fork |
| 600 | 3 has taken a fork |
| 600 | 3 is eating |
| 800 | 1 died |

## Step 2 : initialisation de la structure de table et de celles des philosophes

J'ai enregistre dans ma structure de table les infos recuperer en arguments d'appel a la fonction et je lui ai relie le premier philosophe.
Les philosophes sont donc implementes sous forme de liste chainee circulaire.

En parallele, j'ai cree une liste de enum pour definir un statut a chacun de mes philosophes. Dans ce cadre, aucun philo ne peut voler de fourchettes a un autre si ce n'est pas sont tour de manger. 

L'idee revient a dire que si le nb de philo est pair, alors 1 philo sur 2 commencera sa routine apres que les autres aient manger. Et il y aura donc une attente de repas supplementaire dans le cas ou le nb de philos est impair.

Dans l'idee : ./philo 2 400 200 100
| time | philos |
|-----|----|
| 0 | 1 is eating |
| 200 | 2 is eating |
| 400 | 1 is eating |

etc...

Dans l'idee : ./philo 3 900 300 100
| time | philos |
|-----|----|
| 0 | 1 is eating |
| 300 | 2 is eating |
| 600 | 3 is eating |
| 900 | 1 is eating |

etc...

## Step 3 : creation d'un thread par philosophes

Les threads c'est quoi ?

Pour certains, on a vu dans pipex que fork() nous permet de dupliquer le processus parent/courent pour creer un sous-processus/processus enfant.

Ici, c'est un peu different puisque l'on va creer autant de sous-processus que l'on a de philosophes et qui seront envoyer chacun dans une fonction de type void * pour executer chacun leur routine. 

Or, dans ce contexte, on ne fait pas que dupliquer mais on peut acceder et modifier les donnees en temps reel a partir du thread jusque dans le processus principal.

Globalement, on va utiliser des mutex, qui permettetront (places au bons endroits) de bloquer l'acces d'une variable aux autres threads afin de la lire et/ou de la modifier sans creer de conflits avec ces autres threads. En d'autres termes, les mutex permettent d'eviter la modification/lecture simultanee de donnees pour eviter tout ecrasement ou perte de donnees. Une fois cette etape close, on peut debloquer la ou les variables qui ont ete lues/modifiees.

On utilise egalement le systeme de mutex pour imprimer les sorties afin qu'aucun message ne se chevauche.

Lorsque les conditions de fin de routine sont remplies (tout le monde a mange le bon nb de repqs si av[5] envoye ou quelqu'un est mort), il est imperatif d'utiliser la fonction pthread_join() qui permet d'attendre la fin d'execution de tous les threads avant de clore le programme ou de revenir seulement au processus principal qui est le programme.

## Step 4 : creation de la routine

Dans la conception et la structure de mon programme, il est impossible qu'un philo fasse une action qu'il ne doit pas faire. Ils possedent tous un statut des le depart qui leur permet uniquement de proceder dans un certain ordre. 

Ils vont donc alternativement 1-manger, 2-dormir puis 3-penser. Chaque fonction d'action appelle ft_usleep(). Celle-ci permet d'ecouler le nb de millisecondes recues par intervale de 0,5 (dans mon cas) pour verifier en continue si quelqu'un est mort ou si le philo actuel est mort.

Les threads n'ayant pas le droit de communiquer entre eux, c'est donc ma structure de table qui est mis a jour lorsqu'un philo meurt ou lorsqu'un philo a manger suffisament et c'est seulement ces deux booleens/flags/ints qui pourront etre verifier par chaque philos afin de quitter les threads quand necessaire.
