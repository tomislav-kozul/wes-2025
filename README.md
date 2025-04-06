# wes-2025

Tim 9: Nika Šljubura, Tomislav Kožul i Lovro Jakić


## Spajanje pinova 

Ultrazvucni senzor  

vcc -> +5 V 

Trig -> LED_G 

Echo -> LED_R 

GND -> Ground 

Pojačalo 

Ljubičasta - BTN_4 

Crna – GND 

Crvena – +5 V 
Kod paljenja se čuje zvuk u trajanju 1 sekunde (demonstracija zvučnika)


## Klima 
sadrži 3 različita područja:
- glavna klima odnosi se na klimu automobila
- Ako je temperatura slidera nuža od trenutne temperature i klima je upaljena - pali se plava ledica
- ostale dvije opcije odnose se na grijanje sjedala vozača i suvozača

Esp je spaja na wifi imena S24 i lozinke pass1234!

Implemented features
HOME SCREEN + 6 additional screens
-    For HVAC and seats, and RADIO
FRONT SENSORS
-    Three levels of proximity (40cm – green, 70cm – yellow, 100cm – red)
HVAC
-    Uses on-board temperature sensor to read ambient temperature (SHT3X)
-    Based on user-defined temperature, blue LED represents cooling and switches off when the temp is before that temperature
Wi Fi Connection and SNTP Time Synchronization  
-    for TIME&DATE display on all screens
Audio
-    plays once the screen is switched to front sensors
