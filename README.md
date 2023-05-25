# AoC
Currently working on Advent of Code 2022. 
A small selection of 2020 and 2015 exists too. 

It was supposed to be my repo for only AoC but turned into a collection of interesting projects.

Additionally I added some interesting projects I wrote as part of assignments at Leibniz University Hannover during WinterSemester 2020/2021.
Also one of my first Projects I wrote: schaltjahr.cpp 


--- Tag 1: Kalorienzählen ---

Die Rentiere des Weihnachtsmanns essen normalerweise normales Rentierfutter, aber sie benötigen viel magische Energie, 
um an Weihnachten Geschenke zu verteilen. Dafür ist ihr Lieblingssnack eine besondere Art von Sternenfrucht, 
die nur tief im Dschungel wächst. Die Elfen haben dich auf ihre jährliche Expedition zu dem Hain mit den Früchten mitgenommen.

Um genug magische Energie zu liefern, muss die Expedition bis zum 25. Dezember mindestens fünfzig Sterne sammeln. 
Obwohl die Elfen versichern, dass der Hain reichlich Früchte hat, entscheidest du dich, jede Frucht mitzunehmen, 
die du unterwegs siehst, nur zur Sicherheit.

Sammle Sterne, indem du Rätsel löst. An jedem Tag im Adventskalender werden zwei Rätsel zur Verfügung gestellt; 
das zweite Rätsel wird freigeschaltet, wenn du das erste abgeschlossen hast. Jedes Rätsel gewährt einen Stern. 
Viel Glück!

Der Dschungel ist wahrscheinlich zu dicht bewachsen und schwierig mit Fahrzeugen zu durchqueren oder aus der Luft zu erreichen; 
die Expedition der Elfen erfolgt traditionell zu Fuß. Als deine Boote sich dem Land nähern, beginnen die Elfen, ihren Vorrat an Lebensmitteln zu inventarisieren. 
Ein wichtiger Aspekt ist dabei die Nahrung - insbesondere die Anzahl der Kalorien, die jeder Elf bei sich trägt (deine Rätsel-Eingabe).

Die Elfen notieren abwechselnd die Anzahl der Kalorien der verschiedenen Mahlzeiten, Snacks, Rationen usw., die sie mitgebracht haben, 
jeweils ein Eintrag pro Zeile. Jeder Elf trennt seinen eigenen Vorrat von dem des vorherigen Elfs (falls vorhanden) durch eine Leerzeile.

Angenommen, die Elfen haben ihre Lebensmittel-Kalorien notiert und am Ende die folgende Liste:
1000
2000
3000

4000

5000
6000

7000
8000
9000

10000

Diese Liste repräsentiert die Kalorien der Lebensmittel, die von fünf Elfen mitgeführt werden:

    Der erste Elf trägt Lebensmittel mit 1000, 2000 und 3000 Kalorien bei sich, insgesamt 6000 Kalorien.
    Der zweite Elf trägt einen Lebensmittelartikel mit 4000 Kalorien bei sich.
    Der dritte Elf trägt Lebensmittel mit 5000 und 6000 Kalorien bei sich, insgesamt 11000 Kalorien.
    Der vierte Elf trägt Lebensmittel mit 7000, 8000 und 9000 Kalorien bei sich, insgesamt 24000 Kalorien.
    Der fünfte Elf trägt einen Lebensmittelartikel mit 10000 Kalorien bei sich.

Falls die Elfen hungrig werden und zusätzliche Snacks benötigen, möchten sie wissen, welchen Elf sie fragen müssen: Sie möchten wissen, 
wie viele Kalorien der Elf mit den meisten Kalorien bei sich trägt. In obigem Beispiel sind dies 24000 Kalorien (getragen vom vierten Elf).

Finde den Elf, der die meisten Kalorien trägt. Wie viele Kalorien insgesamt trägt dieser Elf?
