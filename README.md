# cg_proyecto2_ray_tracing


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
    {</code>K<sub>D</sub><code>, </code>K<sub>A</sub><code>},
    {X, Y, Z},
    Radio
}


/POLIGONO/
{
    2,
    {R, G, B},
    {</code>K<sub>D</sub><code>, </code>K<sub>A</sub><code>},
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
</table>