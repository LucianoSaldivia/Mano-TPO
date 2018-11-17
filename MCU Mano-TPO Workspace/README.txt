Para probar Proyecto_Version_XX_X en la pc con la placa infotronic
    -Conectar la placa
    -Correr MCUXpresso
    -Abrir proyecto de la carpeta: Para_Proyecto_Version_02_1 
    -Seleccionar el proyecto desde MCUXpresso ->File->Properties y seguir las instrucciones de las imagenes que estan en esta carpeta para cargar libraries e includes, y obviamente, cambiar las rutas de la carpeta para que quede la ruta en su pc a la carpeta "Librerias_de_Giura", que está dentro de la carpeta que contiene este README.txt , así como las imagenes)
    -Build (Ctrl+B o Martillo)
    -No debería haber errores -> subir a la placa (bug azul) 
    
    -Una vez que tenemos corriendo la placa, abrimos el proyecto de Qt con el mismo nombre de version que el proyecto para MCUXpresso, hacemos Build (Ctrl+B o Martillo)
    -No debería haber errores -> lo corremos (Ctrl+R o Play)
    -Seleccionamos el puerto ( suele ser ttyUSB0 )
    -Conectar
    -En el statusBar (parte más de abajo de la ventana) deberíamos ver "4444", que es el mensaje que se envió desde la placa. La secuencia es la siguiente:
    Apretamos "Conectar", Qt se conecta a la placa, y nos muestra como conectados, una vez hecho esto, envía un mensaje "#S$" a la placa por Puerto Serie, y la placa al recibir esto (podemos verlo en el MCUXpresso), responde con un "\4444\" + '\0' al final
