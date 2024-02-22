# 15-Puzzles

Para generar los PDB's usando las abstracciones hechas ejecute el siguiente comando:

```
./puzzlesPDB.sh
```

Para generar los algoritmos de búsquedas para alcanzar una meta usando las heurísticas previamente generadas ejecute:

```
make -f makeSearch.mk 15-puzzles.<algorigthms>
```

Dónde `<algorithms>` puede ser `aStar` para el algoritmo A* o `idastar` para el algoritmo IDA*.

Luego, para correr el algoritmo ejecute el siguiente comando:

```
./15-puzzles.<algorithms> <testFile>
```

Dónde `testFile` es el nombre del archivo de prueba, el cual debe estar en un archivo `.txt` (un estado inicial por linea).