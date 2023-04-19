# Description

Implements the Dijkstra's shortest path algorithm to find the shortest distance from a source city to all other destination cities. Example input is given as follows:

```
5
Chicago,Duluth(502.71),El Paso(1487.51),Atlanta(718.19),
Duluth,El Paso(1527.35),
El Paso,Phoenix(429.03),Duluth(1527.35),
Atlanta,Duluth(27.64),Chicago(720.14),
Phoenix,Chicago(1753.78),Atlanta(1814.81),
Phoenix
```

(Phoenix is the source city. Chicago, Duluth, El Paso, and Atlanta are destination cities)

# Sample Usage

There are 4 sample input files named inputx.txt.

To run input 1, do

`make exe` 

then

`./exe < input1.txt > output.txt`.

You then can view the output from running input1.txt against exe in output.txt. Make appropriate changes to input files for other cities/distances.
