# whatsbee-sonoff
Nodo de <a href="www.whatsbee.net">whatsbee</a> basado en el hardware de <a href="https://www.itead.cc/sonoff-wifi-wireless-switch.html">Sonoff</a>.
### ¿Qué es WhatsBee?
WhastBee es una moderna plataforma de comunicaciones orientada a los objetos físicos. Utiliza protocolos estándar de gran difusión y código abierto que permiten la conexión de prácticamente cualquier objeto. Ha sido creada poniendo un gran foco en la seguridad de las comunicaciones. 
### ¿Qué es Sonoff?
Sonoff es un producto de Itead Studio que integra un chip ESP8266 con una fuente de alimentación y un relé. Su objetivo es ser un relé inalámbrico que se utilice en el Internet de las cosas. 
###...y Whatsbee-Sonoff?
Hemos escrito un nuevo firmware para Sonoff que nos permita integrarlo en nuestra plataforma WhatsBee el objetivo es poder conectar un objeto físico a nuestra plataforma, de la manera más sencilla posible para el usuario. Sonoff va conectado a la red eléctrica, contiene un relé que puede ser abierto o cerrado utilizando una conexión Wifi y el proquer MQTT de Whatsbee. 
###¿Cómo configurar el Sonoff?
La primera vez que se conecte, despues de cargar el firmware el dispositivo hará un primer intento de conexión a una wifi, al no tener ninguna válida configurada generará un punto de acceso Wifi (en el momento en el que lo genera el led parpadea rapidamente). Simplemente nos tenemos que conectar desde cualquier equipo a ese punto de acceso y abrir en un navegador la dirección http://192.168.4.1/.
En el navegador se abrirá la página de configuración del dispositivo, en la que escribiremos las credenciales de la Wifi (o de hasta tres wifis en la configuración avanzada) y los datos de acceso de WhastBee. 
Para disponer de credenciales para Whatsbee hay que hacer un sencillo proceso de <a href="http://www.whatsbee.net/register.php"> registro </a> en la web de Whatsbee (puedes hacerlo pulsando en el <a href="http://www.whatsbee.net/register.php">link</a>)
Una vez confugurado, en el próximo reinicio el dispositivo se conectará directamente a la wifi y a WhatsBee. A partir de ese momento una pulsación cambiará el estado del relé y actualizará.
Si pulsamos el botón durante un periodo de más de 4 segundos el dispositivo entrará en el modo de configuración.
