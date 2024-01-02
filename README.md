# Robot d'évitement d'obstacles avec Arduino

Ce projet Arduino consiste à construire un robot d'évitement d'obstacles utilisant des capteurs à ultrasons et un contrôle moteur. Le robot peut détecter les obstacles sur son chemin et les contourner.

## Matériel requis
- Carte Arduino (par exemple, Arduino Uno)
- Capteurs à ultrasons (avant, arrière, gauche, droite)
- Pilote de moteur
- Moteurs à courant continu avec roues
- Châssis
- Alimentation (batterie)
- Fils de connexion

## Logiciels requis
- Arduino IDE
- Bibliothèque Adafruit LiquidCrystal

## Schéma de câblage
Incluez un schéma de câblage simple pour aider les utilisateurs à configurer leur matériel.

## Visualisation du Robot
Vous pouvez visualiser le design du robot sur Tinkercad [ici](https://www.tinkercad.com/things/gg93ASuCQoQ-robot2/editel?returnTo=%2Fdashboard%3Fcollection%3Ddesigns).

## Installation
1. Clonez ce dépôt : `git clone https://github.com/votre-nom-utilisateur/arduino-obstacle-avoidance-robot.git`
2. Ouvrez l'IDE Arduino.
3. Chargez le sketch Arduino depuis le dossier `arduino-obstacle-avoidance-robot`.
4. Connectez votre carte Arduino à votre ordinateur via un câble USB.
5. Sélectionnez la carte et le port appropriés dans l'IDE Arduino.
6. Téléversez le sketch sur votre carte Arduino.

## Utilisation
1. Mettez le robot sous tension.
2. L'affichage LCD affichera "Robot Éviteur d'Obstacles."
3. Le robot se déplacera vers l'avant jusqu'à ce qu'un obstacle soit détecté.
4. Si un obstacle est détecté :
   - Le robot s'arrête.
   - Il évalue les environs pour déterminer la meilleure direction de virage.
   - Le robot tourne à gauche, à droite ou recule en fonction des positions des obstacles.
   - L'écran LCD affiche l'action en cours.

## Remarques
- Ajustez la valeur de `DISTANCE_OBSTACLE` dans le code pour définir le seuil de distance de détection des obstacles.
- Assurez-vous des connexions appropriées et de l'alimentation pour un fonctionnement optimal.
  
![Visualisation du Robot]

![ROBOT2](https://github.com/MohammedEttalbi/Robot-d-evitement-d-obstacles-avec-Arduino/assets/127549207/ecd4cf9b-d6d5-4a88-afe1-a1a5b2b81156)

