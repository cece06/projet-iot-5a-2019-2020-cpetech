# Configuration Passerelle - Cloud

Pour le cloud nous avons opté pour deux solutions, la solution Ubidots car facile d’utilisation et en temps réel et Azure car cela permet d’héberger des applications et des données mais propose aussi des services.

Ubidots : 

Pour créer un cloud Ubidots, il faut tout d’abord créer un compte sur https://industrial.ubidots.com. Il est possible d’avoir une version de test gratuitement pendant 30 jours. La plupart des fonctionnalités seront utilisables avec certaines limitations.

Une fois le compte créé, il faut créer un device1. Dans notre cas nous l’avons nommé “cpetech” et il a comme label “cpetech” aussi. Lorsque le device est créé, il faut ajouter les différentes variables2 qui vont être envoyées par le Raspberry Pi. On crée donc 5 variables dans notre cas : les 3 couleurs RGB (red, green and blue), la distance et la couleur finale. Ces cinq variables ont toutes des labels qui seront nécessaire pour notre script python qui va envoyer les données depuis la Raspberry.

Pour l’envoi des données, nous utilisons l’API3 d’Ubidots. Pour cela, le script a tout d’abord été programmé pour envoyer des données générées aléatoirement puis lorsque l’interconnexion entre la carte arduino et la raspberry a été faite, on modifie les variables pour utiliser les données des capteurs. Il faut donc python d’installé sur la raspberry pi pour que cette solution fonctionne.

Pour l’affichage des données en temps réel, nous allons utiliser des Dashboards4. Dans notre cas, les variables étant des nombres hexadécimaux nous ne pouvons représenter ces données sous forme de graphique. Pour la distance, on affichera juste le nombre de m.

1 Device : Pour créer un device, il faut dans le menu principal d’Ubidots aller dans Devices et encore Devices. Pour ajouter un nouveau device, on clique sur le bouton + situé en haut à droite. On choisit ensuite le type de device que l’on souhaite (ceci n’est pas important,  nous avons mis blank device pour notre cas). On choisit ensuite le nom du device et le nom du label du device. Le nom du label est important pour l’utilisation de l’API.

2 Variable : Pour créer une variable, il faut dans le menu principal d’Ubidots aller dans Devices et encore Devices. On choisit ensuite le device créé précédemment et on clique sur le bouton + avec écrit en dessous “Add Variable”. On lui ajoute un nom et un API label, celui-ci sera important pour l’API. Nos données étant en hexadécimal pour la plupart, nous n’avons pas ajouté d’unité.

3 API : Pour pouvoir utiliser l’API, il nous faut générer un token, pour le générer il suffit de cliquer sur le profil tout en haut à gauche et d’entrer dans le menu “API Credentials”. Une petite fenêtre s’affiche avec la clé API et le Token. Dans notre cas il nous faut le token, donc on clique sur “click to show” pour l’obtenir.

4 Dashboards : Pour créer un Dashboard, il faut dans le menu principal d’Ubidots aller dans Data puis Dashboard. On clique sur les 3 barres horizontales à gauche pour ouvrir le menu du dashboard puis le bouton + jaune pour en créer un. On le nomme puis on valide. On clique ensuite sur le bouton + bleu situé en haut à droite pour en créer un. On choisit ensuite le type de widget que l’on veut. Dans notre cas, on veut afficher de l’hexa donc du texte. On choisit donc metric comme widget. On associe ensuite le widget à une variable via le bouton “Add Variables”. On choisit la variable que l’on veut afficher et ensuite on donne un nom à ce dashboard. Dans notre cas la valeur de la variable reçu sera en décimal car l’hexa n’est pas une valeur connu par ubidots. Cependant dans le Dashboard, il est possible d’afficher autre chose que la valeur de la variable. Dans le cadre de notre utilisation, nous allons afficher un contexte. Pour cela il faut activer “Use the HTML editor” puis cliquer sur le bouton “Open editor”. La ligne 1 et 5 étant inutiles, nous les avons supprimées. La ligne où il y a {{value}}, on modifie le mot value par “context.hexa”. hexa est le nom du contexte que nous allons utiliser dans le script python. On accepte donc la modification et on valide en bas à droite pour créer le Dashboard.

# Envoi des données

Envoi des données par script Python au Cloud Ubidots : 

Sur la Raspberry Pi ou BeagleBone, il faut lancer le script send.py. Celui-ci envoie des données grâce à l'API Ubidots.
Pour l'API, il nous faut le token, le label du device et les labels de nos différentes variables. 

La fonction get_hex permet de convertir un nombre décimal en entrée en nombre héxadécimal (dans notre cas on en a besoin)

Les données de nos variables seront entrées dans les lignes "value_x", dans notre cas on génére aléatoirement des nombres car notre Raspberry Pi ne reçoit pas les données des Arduinos.

Dans le payload, on associe les variables à leur valeur. Dans notre cas on utilise des contextes car l'affichage sur Ubidots en Héxadécimal n'est pas possible sinon. Pour ne pas utiliser de contextes il suffit de rentrer les variables comme la ligne de variable_5.

C'est la fonction post_request qui permet d'envoyer les données sous forme Json à Ubidots.

L'envoi des données se fait toutes les x secondes (x = la valeur du time.sleep(x))


# Configuration - Cloud Azure

Dans cette partie, nous allons voir les solutions de cloud de Microsoft (Azure) pour visualiser les données des capteurs et aussi les programmes qui seront implémentés dans la passerelle pour envoyer les données au cloud.

J’ai réalisé deux environnements différents pour visualiser les données des capteurs. Le premier est une base de donnée SQL serveur situé sur le cloud Azure et le second est un hub IOT d’Azure qui permet de connecter et gérer les appareils IoT. Il permet aussi de relier les appareils IoT aux services du cloud.

## Environnement 1 - SQL serveur

Dans un premier temps, il est nécessaire d’avoir accès à internet et d’avoir un compte Azure étudiant (Essaie de 12 mois avec 100$).

Une fois connecté sur votre page de configuration Azure (https://portal.azure.com/#home), il faut créer un SQL serveur dans l’onglet “Toutes les ressources”  (Accueil>Toutes les ressources>Nouveau>créer une base de données SQL).

Dans la configuration du serveur, nous avons plusieurs onglets. 

Dans le premier “de base”, il faut:
 - Choisir votre abonnement Azure (pour les étudiants)
 - Créer un groupe de ressources (“CpeTechGroupRessource”)
 - Mettre un nom de serveur (db)
 - Créer un serveur avec utilisateur/mot de passe et emplacement en france
 - Ne pas prendre pool élastique 
 - Modifier la configuration “Calcul + stockage” de manière à payer moins cher. Pour cela il faut le cliquer dans configurer la bd puis cliquer sur la flèche “vous rechercher l’édition de base,....” puis sélectionner “standard” et enfin appliquer
 - Et pour finir cliquer sur “vérifier et créer”
 - Pour voir les informations sur votre base de données, il faut aller sur votre service sur Accueil>Toutes les ressources ainsi vous pouvez voir le nom de votre serveur (exemple : servercpe.database.windows.net)

Pour passer à la création de la table dans la base de données, il faut installer préalablement “Microsoft SQL Server Management Studio” et avoir une connexion internet autre que CPE pour éviter d’être bloqué par le proxy. Une fois installé, il faut vous connecter sur le logiciel avec le nom du serveur, le nom de l’utilisateur, son mot de passe et aussi en second temps votre compte microsoft azure.


Ensuite pour créer votre table dans la base de donnée, il est nécessaire de sélectionner votre base de donnée (servercpe>Bases de données>db) puis faire une nouvelle requête depuis le menu et exécuter les requêtes SQL suivante : 

Pour la création de la table avec les six colonnes souhaitées dans notre situation:
```javascript
CREATE TABLE CpeTechTable
(
    date_reception DATETIME,
    distance INT,
    couleur VARCHAR(6),
    rouge VARCHAR(6),
    vert VARCHAR(6),
    bleu VARCHAR(6),
);
```
Pour faire un test de fonctionnement de la base et afficher les données insérée:
```
INSERT INTO CpeTechTable (date_reception,distance,couleur,rouge,vert,bleu )
VALUES ('20200120 11:55:00 AM',50,'rouge','FF','00','00');
SELECT * FROM CpeTechTable;
```
Pour finir, nous avons besoin d’un programme python afin d’injecter dans la base de données les informations des capteurs. Ce programme sera insérer sur la passerelle et sera adapter en fonction de la configuration des capteurs. Le nom du programme python est PythonAzure1.py (modification nécessaire entre <>) : 

## Environnement 2 - IoT hub

Dans un premier temps, il est nécessaire d’avoir accès à internet et d’avoir un compte Azure étudiant (Essaie de 12 mois avec 100$).

Une fois connecté sur votre page de configuration Azure (https://portal.azure.com/#home), il faut créer un Hub IoT dans l’onglet “Toutes les ressources”  (Accueil>Toutes les ressources>Nouveau>Hub IoT).

Dans la configuration du Hub, nous avons plusieurs onglets. 
Dans le premier “Base”, il faut:

 - Choisir votre abonnement Azure (pour les étudiants)
 - Créer un groupe de ressources (“CpeTechGroupRessource”)
 - Mettre un nom du hub IoT (hubcpe)

Pour les autres onglets, il faut laisser les données par défaut et ensuite nous pouvons vérifier et créer le hub IoT.

Un appareil IoT doit être inscrit dans le hub IoT pour pouvoir se connecter. Pour cela, Il faut exécuter les commandes suivantes dans le CLI du Cloud Azure qui est en haut de la page à côté de la barre de recherche Azure.


##### Commande - Création de l’appareil:
```az iot hub device-identity create --hub-name {YourIoTHubName} --device-id MyPythonDevice```
##### Commande - Obtenir la chaîne de connexion d’appareil (à sauvegarder dans un bloc note):
```az iot hub device-identity show-connection-string --hub-name {YourIoTHubName} --device-id MyPythonDevice --output table```

Pour finir, nous avons besoin d’un programme python pour envoyer les données des capteurs. Ce programme sera insérer sur la passerelle et sera adapter en fonction de la configuration des capteurs. Avant d’exécuter le programme, il est nécessaire d’installer la bibliothèques requises (pip install azure-iot-device).
Le nom du programme python est PythonAzure2.py(modification de la variable CONNECTION_STRING est nécessaire).

En même temps que l'exécution du programme, nous pouvons voir la réception des donnée en utilisant une commande sur le CLI d’Azure:

 ##### Commande - Lecture des données (Remplaçant YourIoTHubName par le nom du hub):
```az iot hub monitor-events --hub-name {YourIoTHubName} --device-id MyPythonDevice```

Source : ```https://docs.microsoft.com/fr-fr/azure/iot-hub/quickstart-send-telemetry-python#code-try-0```
