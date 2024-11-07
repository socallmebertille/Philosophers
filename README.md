# Philosophers
I never thought philosophy would be so deadly

## Step 1 : comprehension du sujet

L'idee est de pouvoir faire vivre nb_philo philosophes selon une routine bien precise (1-manger / 2-dormir / 3-penser) qui doit durer au maximum time_to_die millisecondes. 
Pour ce faire, un plat de spaghettis est dispose au centre de la table mais chaque philosphe dispose d'une seule fourchette. Etant donne que pour se servir dans un tel plat, il est necessaire d'avoir une 2eme fourchette, on considere que les philosophes mangent lorsqu'ils ont reussi a acceder a leur fourchette (a leur droite) et a celle de leur voisin de gauche. 
De fait, ils ne peuvet pas manger tous en meme temps. 

On peut dors et deja determiner les cas dans lesquels les philosphes vont mourir :

- s'il n'y a qu'un seul philosophe (car une seul fourchette a sa dispo)
ex : ./philo 1 800 200 100
0 1 has taken a fork
800 1 died

- s'il y a nb pair de philo ET que time_to_die / 2 < time_to_eat
ex : ./philo 2 300 200 100
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
300 1 is thinking
310 2 died

- s'il y a nb impair de philo ET que time_to_die / 3 < time_to_eat
ex : ./philo 3 800 300 100
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
300 1 is sleeping
300 2 has taken a fork
300 2 has taken a fork
300 2 is eating
400 1 is thinking
600 2 is sleeping
600 3 has taken a fork
600 3 has taken a fork
600 3 is eating
800 1 died

## Step 2 : initialisation de la structure de table et de celles des philosophes

J'ai enregistre dans ma structure de table les infos recuperer en arguments d'appel a la fonction et je lui ai relie le premier philosophe.
Les philosophes sont donc implementes sous forme de liste chainee circulaire.
En parallele, j'ai cree une liste de enum pour definir un statut a chacun de mes philosophes. Dans ce cadre, aucun philo ne peut voler de fourchettes a un autre si ce n'est pas sont tour de manger. L'idee revient a dire que si le nb de philo est pair, alors 1 philo sur 2 commencera sa routine apres que les autres aient manger. Et il y aura donc une attente de repas supplementaire dans le cas ou le nb de philos est impair.
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

