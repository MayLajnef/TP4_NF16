Soit E= {e1, e2, …, eN} un ensemble de N entiers distincts. On souhaite représenter un tel ensemble
en utilisant un arbre binaire de recherche.
Dans une représentation classique, la clé de chaque sommet correspondrait à un élément de
l’ensemble E.
Mais pour utiliser moins de mémoire, nous allons représenter l’ensemble d’entiers de manière
plus compacte en profitant du fait que plusieurs éléments de l’ensemble peuvent être consécutifs,
formant alors un intervalle de valeurs entières qui peut être caractérisé par sa borne inférieure
et sa borne supérieure. Chaque sommet de l’arbre binaire de recherche correspond alors à un
intervalle de valeurs entières consécutives.
