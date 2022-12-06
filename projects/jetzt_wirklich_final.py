#!/usr/bin/python
#code by Stephan Jokiel & Hanna Klamt
#coding=utf-8

#ds18b20_auslesen.py

#---------------

from Adafruit_IO import Client, Data
aio = Client("CelsiusFIAE21K", "aio_VYyt00HwSkecTtEWALNxIUHGbFDV")


import os, sys, time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(26,GPIO.OUT)
GPIO.setup(12,GPIO.OUT)
GPIO.output(12, False)
GPIO.output(26, False)
# Erstellen der Funktion zum Ermitteln der aktuellen Temperatur
buttonstate = aio.receive('test').value
print(buttonstate)
def aktuelleTemperatur():


    # 1-wire Slave Datei lesen

    file = open('/sys/bus/w1/devices/10-000803a4cdf5/w1_slave')

    filecontent = file.read()

    file.close()

    # Temperaturwerte auslesen und konvertieren

    stringvalue = filecontent.split("\n")[1].split(" ")[9]

    temperature = float(stringvalue[2:]) / 1000


    # Temperatur ausgeben

    rueckgabewert = '%1.2f' % temperature

   #return(rueckgabewert)
    return(temperature)


# Deklaration der Variablen

schleifenZaehler = 0

schleifenAnzahl = 20

schleifenPause = 1



# Ausgabe der aktuellen Temperatur und der Nummer des Schleifen-Durchlaufes

#print("Temperaturabfrage fuer ", schleifenAnzahl," Messungen alle ", schleifenPause ," Sekunden gestartet")
print("Temperaturmessung gestartet, warte auf Buttonstate = ON, if it's on, start getting temp")


test = aio.feeds('celsiusfiae21k')
boolwert = 0
while True:

    buttonstate = aio.receive('test').value
    time.sleep(1)

    if buttonstate == 'ON':
        print("Messung an")
    elif buttonstate != 'ON' and boolwert == 0:
        print("Messung off")
        boolwert = 1

    while str(buttonstate) == 'ON':
        boolwert = 0
        buttonstate = aio.receive('test').value
        messdaten = aktuelleTemperatur()
        aio.send_data(test.key, messdaten)
        print("Aktuelle Temperatur : ", messdaten, "C","in der ", schleifenZaehler, ". Messabfrage")
        time.sleep(schleifenPause)
        schleifenZaehler = schleifenZaehler + 1
        #print(messdaten)
        if messdaten <0:
            GPIO.output(26,True)
            GPIO.output(12,False)
        elif messdaten > 27.00 :
            GPIO.output(26,True)
            GPIO.output(12,False)
        else:
            GPIO.output(26,False)
            GPIO.output(12,True)

# Ausgabe zum Ende des Programmes

print("Temperaturabfrage beendet")
GPIO.output(26,False)
GPIO.output(12,True)
