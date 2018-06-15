
Legend of Zelda 3D game in OpenGL 3. More details in the statement [PDF](Assignment2.pdf).

## 1. How to run the game

### First compile:

```
cmake CMakeLists.txt
make
```

### Then run the executable:

```2
 ./graphics_assign2
```

## 2. Rules and the Controls :
* Move the boat and kill the enemies
* After scoring some points, a boss will appear who is difficult to kill
* There are rocks on the sea. Colliding with them leads to loss of life
* You can shoot torpedos at the rocks/enemies/monsters to destroy them
* A wind may appear at certain intervals of time and it can move the boat along the wind direction
* There are barrels floating on the sea with gifts/powerups available
* On killing a boss, you get a booster which increases your speed for some amount of time
* The game can be viewed through different camera views such as HELICOPTER, FOLLOW, BOAT ...

##### Keyboard Controls

|   KEY |              ACTION |
| ----: | ------------------: |
|     f |         fire cannon |
| Space |                Jump |
|     q |                quit |
|    up |        move forward |
|  down |       move backword |
|  left |    rotate rightward |
| right |     rotate leftward |
|     c | change camera  view |
|       |                     |





## 5. Additional Features

* The game has background audio implemented using threading.
* Zooming, Panning and different views were implemented.
* Scoring scheme was implemented segregating enemies by color scheme.
* Lives were implemented.
* Time elapsed is shown along with the lives left.
* Barrels have gems/powerups.

License
-------
The MIT License

Copyright &copy; 2017 Utkarsh <utkarshazad98@gmail.com>

Music Credits: Hans Zimmer (www.hans-zimmer.com/)
