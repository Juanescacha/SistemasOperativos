En esta carpeta estarán todos los archivos que dan soluciń a las preguntas
del capítulo 5.

* [Ejercicio 1](ej1.c) 
* Podemos observar la variable en el proceso hijo no ha tenido ningun cambio, al igual
  que en el padre, cuando el hijo y el padre hacen sus respectivos cambios a la variable
  lo que evidenciamos es que ambos toman la variable desde el valor inicial (10) y hacen el  cambio
  el hijo la multiplica por 10 y el padre por 20. Luego observamos que los resultados son los esperados.



* [Ejercicio 2](ej2.c)
* Aqui se evidencia que los dos procesos (padre e hijo) pueden acceder al archivo.
  vemos que cuando escriben simultaneamente reemplazan lo que habia en el archivo (lo sobreescriben)
  y ambos dejan su mensaje en el guardado. 


* [Ejercicio 3](ej3.c)
* Para solucionar este problema, en el proceso hijo detuve el proceso padre con la funcion kill() enviandole
  como argumento el pid del proceso padre.
  Luego en el proceso padre le envio la señal SIGCONT para que continue el proceso y le envio el metodo
  sig_handler que es el que mostrara el mensaje de "adios", por ultimo uso la funcion pause() que hace
  que el proceso se duerma hasta que llegue la señal.
  de esta manera se puede ver como el hijo es quien envia primero el mensaje sin tener que utilizar
  el llamado wait().


* [Ejercicio 4](ej4.c)
* en este ejercicio es donde se muestra el funcionamiento de las variantes de exec(): execl(), execle(),
  execv(), etc. 



* [Ejercicio 5](ej5.c)
* En este ejercicio lo que vemos cuando se usa el wait() en el padre es que el proceso efectivamente espera
  a que primero se ejecute el proceso hijo, y el wait retorna el pid del hijo, cuando se usa el wait en el hijo
  lo que sucede es igual, el hijo espera a que primero se ejecute el padre, pero esta vez el valor que devuelve
  el wait es -1.


* [Ejercicio 6](ej6.c)
* El waitpid() es util cuando tenemos varios procesos hijos, en wait se espera a que cualquiera de los hijos
  que llama  a la funcion wait cambie de estado; en waitpid se suspende el proceso cuando el hijo que ha sido
  especificado con el argumento pid cambia de estado. 


* [Ejercicio 7](ej7.c)
* Al realizar la llamada a printf() despues de cerrar el output(STDOUT_FILENO) vemos que 
  si se creo un proceso hijo, pues el resultado de compilar es el mensaje del padre referenciando
  el pid del hijo, pero el hijo no muestra su salida.
