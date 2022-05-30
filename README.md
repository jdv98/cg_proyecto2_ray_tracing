# cg_proyecto2_ray_tracing

# Uso

Por defecto la aplicación si se corre sin ningún parámetro, esta usará el archivo escenario.txt dentro de la carpeta archivos y generará una imagen .avs con resolución 1008 x 567.

Si se desea otro tipo de formato de imagen entonces seguir los siguientes pasos

```
./bin/main 
           escenario_archivo
           escenario_archivo formato_imagen
           escenario_archivo formato_imagen width height
```
#### Ejemplos

```
./bin/main
./bin/main escenario
./bin/main escenario jpg
./bin/main escenario jpg 504 283

make run
make run i="escenario" t="jpg" w="504" h="283"

```

# Escenario

#### Estructura txt

<pre>
<code>
//AMBIENTE/
{
    5,
    </code>I<sub>A</sub><code>
}


/FOCO/
{
    0,
    {</code>I<sub>P</sub><code>, </code>C<sub>1</sub><code>, </code>C<sub>2</sub><code>, </code>C<sub>3</sub><code>},
    {X, Y, Z}
}


/OJO/
{
    3,
    {X, Y, Z}
}


/FRAME/
{
    4,
    {</code>X<sub>1</sub><code>, </code>Y<sub>1</sub><code>, </code>Z<sub>1</sub><code>},
    {</code>X<sub>2</sub><code>, </code>Y<sub>2</sub><code>, </code>Z<sub>2</sub><code>}
}


/ESFERA/
{
    1,
    {R, G, B},
    {</code>K<sub>D</sub><code>, </code>K<sub>A</sub><code>, </code>K<sub>N</sub><code>, </code>K<sub>S</sub><code>},
    {X, Y, Z},
    Radio
}


/POLIGONO/
{
    2,
    {R, G, B},
    {</code>K<sub>D</sub><code>, </code>K<sub>A</sub><code>, </code>K<sub>N</sub><code>, </code>K<sub>S</sub><code>},
    { 
        [
            {</code>X<sub>1</sub><code>, </code>Y<sub>1</sub><code>, </code>Z<sub>1</sub><code>},
            {</code>X<sub>2</sub><code>, </code>Y<sub>2</sub><code>, </code>Z<sub>2</sub><code>},
            {</code>X<sub>3</sub><code>, </code>Y<sub>3</sub><code>, </code>Z<sub>3</sub><code>},
            {</code>X<sub>4</sub><code>, </code>Y<sub>4</sub><code>, </code>Z<sub>4</sub><code>}
        ],
        [
            {</code>X<sub>1</sub><code>, </code>Y<sub>1</sub><code>, </code>Z<sub>1</sub><code>},
            {</code>X<sub>2</sub><code>, </code>Y<sub>2</sub><code>, </code>Z<sub>2</sub><code>}
        ],
        .
        .
        .
    },
    Radio
}
</code>
</pre>


<table>
<tr>
    <th colspan="2">Glosario</th>
  </tr>
<tr>
    <td>K<sub>D</sub></td>
    <td>Coeficiente de reflexión difusa</td>
</tr>
<tr>
    <td>K<sub>A</sub></td>
    <td>Coeficiente de iluminación ambiente</td>
</tr>
<tr>
    <td>I<sub>P</sub></td>
    <td>Intensidad de la luz del foco</td>
</tr>
<tr>
    <td>I<sub>A</sub></td>
    <td>Iluminación ambiente</td>
</tr>
<tr>
    <td>C<sub>1</sub>, C<sub>2</sub>, C<sub>3</sub></td>
    <td>Caída de la luz</td>
</tr>
</table>