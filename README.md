# ASD1_LABO1

# Fonction 4 - f(..)
C'est une fonction récursive qui s'appelle 3 fois et effectue 2 additions à chaque appelle. 
En développant sous forme d'arbre, on peut voir que l'arbre a une profondeur de N et on se retrouve donc avec
une complexité d'O(3^N).

| N           | 5           | 6           | 7           | 8           | 9           | 10          |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| Théorique   | 243         | 729         | 2187        | 6561        | 19683       | 59049       |
| Empirique   | 242         | 728         | 2186        | 6560        | 19682       | 59048       |

<INSERT_GRAPHE>

# Fonction 6 - random(..)
La fonction `push_back` possède une compléxité constante, O(1) et est executé N fois. 
La fonction random possède donc une complexité de O(N) * O(1) = O(N) 
```
Constant (amortized time, reallocation may happen).

If a reallocation happens, the reallocation is itself up to linear in the entire size.
```
c.f. : http://www.cplusplus.com/reference/vector/vector/push_back/

| N                 | 1000        | 5000        | 10000       | 50000       | 100000      | 1000000     |
| ----------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| Théorique         |             |             |             |             |             |             |
| Temps d'exécution |             |             |             |             |             |             |

<INSERT_GRAPHE>
