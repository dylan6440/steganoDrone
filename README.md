# steganoDrone

# Projet Final - Formation C++ Embarqué - Ynov Bordeaux 

# Contexte
Nous sommes en 2024, pendant la 3ème guerre mondiale. L'un de nos drones a photographié une base militaire ennemie de nuit (voir annexe, fichier DroneIMG37337.png) et dissimulé les coordonnées du lieu (37°42'41.9"S 144°59'33.0"E). Cette image doit être récupérée et analysée pour déterminer les actions à mener.

# Objectifs
1. Transmettre l'image et son information cachée en utilisant de la stéganographie et le protocole MQTT.
2. Récupérer l'image et découvrir les coordonnées du cliché.

# Organisation
- Pour ce projet en groupe, vous serez séparés en deux équipes (équipe Drone et équipe Base). Vous allez partager un nouveau GitHub public et publier votre code et captures d'écran, sur ce repo en séparant les deux projets (Drone et Base).
- Vous proposerez des pull requests, branches, commits etc. entre les membres de l'équipe ou du groupe si vous êtes seul dans l'équipe.
- Le PAQL en annexe devra être respecté.
- Aucun code commenté ne sera commité dans la branche principale release/main.

# Equipe Drone
Vous aurez pour mission de créer un programme console avec Qt en C++ qui charge le fichier DroneIMG37337.png et y ajoute via un algorithme au choix autre que steghide, les coordonnées GPS 37°42'41.9"S 144°59'33.0"E. Le fichier sera envoyé sur le broker: mqtt://broker.emqx.io:1883, topic /ynov/bordeaux/NomDuGitHubDuGroupe avec un QoS 2. Le programme devra être le plus léger possible, chaque tentative d'optimisation faisant l'objet de la création d'une branche dans le GitHub.

# Equipe Base
Vous aurez pour mission de créer un programme graphique avec Qt Design en C++ qui se connecte au broker: mqtt://broker.emqx.io:1883 et s'abonne au topic: /ynov/bordeaux/NomDuGitHubDuGroupe avec un QoS 2. Une fois le fichier récupéré, vous devrez découvrir les coordonnées cachées dans l'image et afficher l'image ainsi que les coordonnées GPS. Le programme devra être le plus léger possible, chaque tentative d'optimisation faisant l'objet de la création d'une branche dans le GitHub.




# Installation librairie qtmqtt :  
- git clone https://github.com/qt/qtmqtt.git --branch 5.15.2 
- cd qtmqtt
- sudo ~/Qt/5.15.2/gcc_64/bin/qmake 
- sudo make
- sudo make install
# Fichier .pro :
- ajouter la ligne : QT += mqtt


# Annexes
Le fichier DroneIMG37337.png contenant l'image à traiter sera fourni.

# PAQL
Le PAQL (Plan d'Assurance Qualité Logiciel) sera fourni.
