# Luminis

Fényerő kapcsolási határérték beállítása:
1. Soros monitor megnyitása
  - Hardver csatlakoztatása usb kábbellel a számítógéphez
  - Arduino Ide megnyitása
  - Port beállítása: Menüsorvól: Eszközök/Port --> megfelelő port kiválasztása
  - Soros Monitor megnyitása: Eszközök/Soros monitor vagy Ctrl+Shift+M
  - Jobb alsó sarokban a "nincs sorvég" és "9600 baud" legyen beállítva
  - Ha minden működik, akkor a következő adatok jelennek meg másodpercenként:
    - Mert fenyero: 158
    - A beallitott kapcsolasi hatarartek: 333
    - Sotet van/Világos van
    
2. Fényerő kapcsolási határérték beállítása:
  - Bal felső beviteli mezőbe írjuk be az új kapcsolási határértéket, 0-1023 közötti értékek megfelelőek
  - Nomjuk meg a külség gombot (enter), a következő jelenik meg:
    - Az uj kapcsolasi hatarertek: 777
    - Mert fenyero: 232
    - A beallitott kapcsolasi hatarartek: 777
    - Sotet van

Amennyiben a mert fényerő alacsonyabb mit a beállított, az eszköt azt érzékeli, hogy sötét van. Vagyis ha a kapcsolási határértéket növeljük, a világítás előbb (nagyobb fénynél) fog kapcsolni.
    


    
Firmware frissítés:
Open your sketch
Open the IdoRele.ino

Select your board type and port
Select Tools > Board > Arduino AVR Boards > Arduino Nano.

NOTE: We have updated the Nano board with a fresh bootloader. 
Boards sold by us from January 2018 have this new bootloader, while boards manufactured before that date have the old bootloader. 
First, check that Tools > Board > Boards Manager shows you have the Arduino AVR Boards 1.16.21 or later installed. 
Then, to program the NEW Arduino NANO boards you need to chose Tools > Processor > ATmega328P. 
To program old boards you need to choose Tools > Processor > ATmega328P (Old Bootloader). 
If you get an error while uploading or you are not sure which bootloader you have, try each Tools > Processor menu option until your board gets properly programmed.

Upload and Run your first Sketch
To upload the sketch to the Arduino Nano, click the Upload button in the upper left to load and run the sketch on your board:

UNO Upload

Wait a few seconds - you should see the RX and TX LEDs on the board flashing. 
If the upload is successful, the message "Done uploading." will appear in the status bar.
