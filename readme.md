# Commande de Servomoteur

Le présent mini-projet est orienté vers la commande de servomoteur. Ce type 
d'application est très commun dans des projets plus important de robotique.
Ainsi, ce mini-projet s'insérant de le cadre du cours de programmation de 
microcontrôleur prépare des applications futures.

## Objectif

Commander un servomoteur pour faire une rotation de 180° dans les deux sens de 
rotation.
Ce projet est certe un projet de programmation de µC mais il relève aussi de 
l'électronique. A cet effet, ce projet vise aussi à acquérir les fondamentaux 
électroniques nécessaire pour l'implémentation et mettre en oeuvre un 
microcontrôleur.

## Le servomoteur

### Description

Un servo-moteur est un type de moteur électrique. C'est un dispositif 
typiquement utilisé en modélisme pour, par exemple, contrôler la direction 
d'une voiture télécommandée.

Sur un servo-moteur, l'angle peu varier d'un angle fixe entre 0 et 180° 
en fonction du signal envoyé.  Un servo-moteur comprend :

- Un moteur électrique (continu), généralement assez petit.
- Des engrenages réducteur en sortie du ce moteur (pour avoir moins de vitesse 
et plus de couple ou de force).
- Un capteur type "potentiomètre" raccordé sur la sortie.

Il s'agit donc d'une résistance qui varie en fonction de l'angle, ce qui 
permet de mesurer l'angle de rotation sur l'axe de sortie.
Un asservissement électronique pour contrôler la position/rotatop, de cet axe 
de sortie pour le maintenir à la bonne position.

### La commande du servomoteur

Afin de commander le servomoteur, il faut envoyer une impulsion et c'est le 
temps que durera cette impulsion qui déterminera l'angle du servo-moteur.

ce temps d'impulsion est de quelques de quelques millisecondes et doit être 
répété à intervalle régulier (toutes les 20 ms à 50ms).

Si le temps d'impulsion varie d'un fabricant  à l'autre, les valeurs suivantes 
sont assez standard:

- 1.25 ms = 0 degré
- 1.50 ms = 90 degrés
- 1.75 ms = 180 degrés

### Mise en oeuvre

Le raccordement d'un servomoteur s'effectue à l'aide de trois (03) fils:

- La masse (GND)
- L'alimentation (+5V)
- La commande

## Configuration

La commande du servomoteur se fera dans le cadre de ce projet à l'aide du 
microcontrôleur ATMEGA 168 et la programmation en C.

La commande du moteur sera connecté à la broche `PB0`

						|				  |	Servomoteur
			       ATMEGA168	|			    GND---|
						|				  |
					PB0	|---------------------------------| Commande 
						|				  |
						|			    VCC---|

## Lien utile

- [Wikiversity](https://fr.wikiversity.org/wiki/Micro_contr%C3%B4leurs_AVR)
- [Efundies](https://efundies.com/category/avr/)
- [Servomoteur](https://eskimon.fr/tuto-arduino-602-un-moteur-qui-a-de-la-t%C3%AAte-le-servomoteur)
- [Explore Embedded](https://exploreembedded.com)
- [Electrowings - Servomoteur](http://www.electronicwings.com/avr-atmega/servo-motor-interfacing-with-atmega16)
