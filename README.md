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
    

    
