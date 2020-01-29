# Configuration Raspberry PI (3 B+)

///// Configuration PI /////

--se connecter à PI en ssh--

sudo -i

apt update
apt upgrade

apt install python-pip
pip install pyserial
pip install requests

nano /boot/config.txt

--ajouter ces lignes à la fin du fichier--

dtoverlay=pi3-miniuart-bt
enable_uart=1

nano /boot/cmdline.txt

--supprimer la ligne suivante--

console=serial0,115200

--redémarrer la PI--

reboot

--se re-connecter à PI en ssh--

sudo -i
cd /opt
mkdir py
cd py


git *recuperer le code sur git*

python serial.py


![alt Beaglebone](../images/bbb.jpg)
