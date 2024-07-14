
## Babel VoIP Application


Babel est une application de communication vocale en temps réel, basée sur la technologie VoIP (Voice over Internet Protocol). Elle est implémentée en C++ et utilise les bibliothèques AudioPort et Opus pour l'enregistrement et le traitement audio.
## Installation
Pour installer Babel, vous devez avoir les bibliothèques AudioPort et Opus installées sur votre système. Une fois ces bibliothèques installées, vous pouvez télécharger le code source de Babel à partir du référentiel GitHub.
## Utilisation
Babel se compose de deux programmes distincts: babel_server et babel_client.
## babel_server
babel_server est le programme serveur qui gère les connexions clients et les échanges de données audio entre eux.

Pour exécuter babel_server, vous devez exécuter la commande suivante dans votre terminal:

./babel_serve
## babel_client
babel_client est le programme client qui vous permet de vous connecter à d'autres clients et d'échanger des données audio avec eux.

Pour exécuter babel_client, vous devez exécuter la commande suivante dans votre terminal:

css
Copy code
./babel_client

Une fois connecté, vous pouvez utiliser les commandes suivantes dans babel_client:

[List, Connexion]
