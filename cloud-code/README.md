# Configuration Passerelle - Cloud

Envoi des données par script Python au Cloud Ubidots : 

Sur la Raspberry Pi ou BeagleBone, il faut lancer le script send.py. Celui-ci envoie des données grâce à l'API Ubidots.
Pour l'API, il nous faut le token, le label du device et les labels de nos différentes variables. 

La fonction get_hex permet de convertir un nombre décimal en entrée en nombre héxadécimal (dans notre cas on en a besoin)

Les données de nos variables seront entrées dans les lignes "value_x", dans notre cas on génére aléatoirement des nombres car notre Raspberry Pi ne reçoit pas les données des Arduinos.

Dans le payload, on associe les variables à leur valeur. Dans notre cas on utilise des contextes car l'affichage sur Ubidots en Héxadécimal n'est pas possible sinon. Pour ne pas utiliser de contextes il suffit de rentrer les variables comme la ligne de variable_5.

C'est la fonction post_request qui permet d'envoyer les données sous forme Json à Ubidots.

L'envoi des données se fait toutes les x secondes (x = la valeur du time.sleep(x))
