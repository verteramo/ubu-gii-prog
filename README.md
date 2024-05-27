### Calificación: 8,30

### Retroalimentación:

Antes de nada, felicitarte por tu trabajo y por la claridad de tu código.
- Comentario de programa presente.
- No puedes emplear cadenas, es un conocimiento del tema B. Debes emplear las herramientas hasta el tema A, que es lo que en realidad se evalúa en este ejercicio.
- Aportas algunos defines que son útiles. Se te felicita por tu esfuerzo en esta parcela.
- En mi opinión, emplear un sólo define para todo un menú, por ejemplo, no ayuda mucho al mantenimiento. En tu caso, dada la manera ordenada de plantearla, me puede parecer una idea algo más acertada.
- Prototipos de función presentes, bien documentados.
  - anomalies(): el valor "0.1" sería muy útil como argumento. 
  - copy(): amplia un poco el nombre, por lo demás de acuerdo.
- A pesar de tu claridad, creo que no es una buena idea disponer de nombres de función como "opcion1"; un cambio en requisitos de usuario te deja un poco colgado de la brocha.
  - main(): de acuerdo, pero "gasta" alguna variable auxiliar. Ahora son baratas.
  - option0: es hora de que alguien reparase en estas cosas. Debes aportar, por educación, un return en las funciones void.
  - option2: debes darte cuenta de que es una función muy similar a la anterior. Valores como "25000" deben ser constantes, defines o etiqueta de tipo enumerado.
  -Opción 3: mejor si independizas el crear el binario de la búsqueda binaria. Son dos cosas que, aunque están relacionadas, no deben ser una secuencia. Salvo que, por ejemplo, hubiese cambiado el fichero original, y en todo caso, es algo a "disparar" fruto de ese cambio, más que de la búsqueda binaria.
  - find(): tras el fseek debes verificar el EOF; no hay cosas más insegura que el contenido de un fichero.
  - anomalies(): "10" debe ser constante, define o mejor argumento. Tras la lectura de fichero es necesario verificar el EOF; no os quedéis sólo con el valor devuelto por fscanf.
En todo caso, se trata de un ejercicio excelente, el mejor que hemos corregido con diferencia. Se te anima a seguir mejorando, a pesar de tu buen nivel.
