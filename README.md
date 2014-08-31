Tools-Polybox
=============

This repository contains some scripts usefull

If you start with a fresh 12.04 Ubuntu, just start the main script by calling 'make':

make install


The makefile will start all the install procedure.
This main script is under ./Scripts/isntall-all.sh. It will start each installation and setup script 1 by 1.
The script will ask you some confirmation sometime.

During the setup, your computer will restart. Don't be afraid.
After each reboot, you have to call 'make install' again. Nothing more. Just call it again. Everything will continue.
We cannot do a script withotu restart since we are patching the kernel with RealTime component (RTAI).

It's very important. If you don't restart the script, no magic will happends and you will miss some important part.


Francais
==============


Progrès
---------------

Le dépôt est actuellement entierement fonctionnel. Il vous permettra d'installer tout l'environement nécessaire à l'utilisation de la Polybox. 
Ces scripts peuvent nécessiter quelques modifications au fil du temps, afin de les maintenir utilisable (dépendances rompus, paquets manquants, nouvelles technologies, obsolécence etc...)

Dernière modification de la documentation : 1 Septembre 2014.

Plateforme
--------------

Les scripts et la chaine d'installation a été dévelopés et testés pour une Ubunutu 12.04 LTS, 32bits avec KDE comme interface graphique. 
Cependant, il est tout a fait possible d'utiliser les scripts sur un autre Linux, modulo des modifications propre à la cible. 

Le système d'exploitation est récupérable a cette adresse :
  * ISO : http://cdimage.ubuntu.com/kubuntu/releases/precise/release/kubuntu-12.04.4-desktop-i386.iso
  * Torrent : http://cdimage.ubuntu.com/kubuntu/releases/precise/release/kubuntu-12.04.4-desktop-i386.iso.torrent
  * Autre : http://cdimage.ubuntu.com/kubuntu/releases/precise/release/

Installation (Rapide)
----------------------

Pour installer l'intégralité des outils et de la configuration Polybox, plusieurs étapes sont nécessaires et demande un certain temps (entre 1 et 5 heures, en fonction de la machine). Cependant, la majorité des étapes ne demandent pas d'intervention humaine directe.


Préparation
---------------

La première étape consiste a récuperer un premier paquet essentiel à la récuperation des scripts.

  1. Ouvrer un Terminal (Console). Pour cela, plusieurs solutions :
    * Alt+F2 > taper "terminal" puis entrer pour selectionner l'application
    * Menu K > Applications > Système > Terminal
  2. Une fois la console ouverte, recuperer le paquet "Git" et "Make"
    * sudo apt-get install git make
    * Entrer votre mot de passe puis valider
  4. Enfin, vous êtes pret à recuperer le dépôt, donc les scripts. Dans le terminal :
~~~
      git clone https://github.com/skapin/Tools-Polybox.git 
~~~


Installation
--------------

Le dépôt nouvellement récuperé se trouve dans votre répertoire personel :
  * /home/USER_NAME/Tools-Polybox/

Placer vous dans le bon dossier :
~~~
   cd ~/Tools-Polybox
~~~
  
Puis, lancer le script d'installation principal via le Makefile :
~~~
  make install
~~~

Il vous sera alors demander de valider le script par deux fois à son lancement, puis de fournir le mot de passe root.
Enfin, le script va se lancer. Chaques étapes est vérifiée automatiquement, et toute erreurs bloquera le script avec message explication en sortie (de couleur rouge). Il vous sera alors nécessaire d'intervenir manuellement pour corriger l'erreure, puis relancer le script. 
Votre ordinateur redemarrera a plusieurs reprise durant le processus d'installation, en particulier lors du patch du kernel. Il vous sera alors necessaire de relancer le script d'installation. L'avancement de l'installation n'est pas perdu, et le script reprendra au dernier point de sauvegarde atteind. 

Liste des différentes étapes à titre indicatif :
  1. Récupération des outils/logiciels
  2. CNC - Partie 1 : Patch du Kernel et mise en place du RunTime
  3. Redémarrage
  4. CNC - Partie 2 : Récuperation de LinuxCNC + Compilation
  5. Scan ( obsolete )
  6. Imprimante 3D
  7. Logiciel de contrôle Polybox
  8. Mise en place de l'environement (icones, menu, bash_rc, widget, ...)
  9. Fin

Toute relance du script alors que l'installation est marqué comme terminé entrainera l'affichage d'un message d'indication sur le terminale. 

L'état d'avancement du script est stocké dans un fichier caché (préfixé par un ., soit ls -a pour l'afficher). Il vous est possible de modifier manuellement l'avancement pour "tromper" le script, ou tout simplement supprimer le fichier popur forcer une réinstallation complète.

A terme, une version acceptant des arguments en entrées est envisagée.




English
==============

















