# FishingGame
Console Fishing Game for a online C++ course.

The project uses C++ without external libraries.
Libraries used:
iostream, chrono,	thread,	random, string, assert.h,	Windows.h, fstream,	ctime	

The project has simple uses of Macros, Templates, Random Number Generation, Inheritance, File streams, Passing by reference and more.

All the fish classes are derived from FishBase.
FishBase contains weigth, maxWeight, minWeight, breed and a RandomizeWeight function that uses the maximum and minimum weight.
Each fish breed has its own max and minimum weight, as well as it's own breed name. 




KÄYTTÖOHJEET:

Sovelluksen käynnistäessä tulee valita ensin syötti käyttäen numeroita 1-4.
Paina Enter näppäintä kun haluttu numero on valittu.
Kalastuksessa kestää muutama sekuntti riippuen valitusta syötistä ja napatusta kalasta.
Kun kala on saatu, tulee näytölle saadun kalan nimi punaisella, ja ohjelma kysyy halutaanko kalastaa uudelleen.
Painaessa y:tä ja vahvistaen valinnan Enter näppäimellä, kalastus käynnistyy uudelleen.
Painaessa n näppäintä, ohjelma kysyy että haluatko vaihtaa syöttiä.
Painaessa y:tä ja vahvistaen valinnan Enter näppäimellä, tulee syötinvalinta näkyviin konsolille.
Painaessa n näppäintä ja vahvistaen valinnan Enter näppäimellä, kalastu loppuu ja ruudulle tulee näkymään saadut kalat ja niiden painot.
Kalojen kokonaispaino näkyy vihreällä.
Viimeisin kokonaispaino tulostuu Fish.txt tiedostoon.
Jos käyttäjä on kalastanut aikaisemmin, tulee viimeisimmän kerran kokonaispaino näkyviin aloitus näkymässä.


