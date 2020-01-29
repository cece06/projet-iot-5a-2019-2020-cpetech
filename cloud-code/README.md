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
