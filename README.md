# Paint_Like_App
Forked from my own git. 

The idea of the project was to develop a trial version of paint app + CAD app (Sort of replicating the basic features of AutoCAD).

Technologies used -> 
1. QT 5.12
2. OpenGL 

App Overview ->
1. Button Ribbon -> Toggle buttons. Select and start drawing on the canvas. 
2. Drawing Canvas -> Draw using mouse. Select the required number of points by left clicking at the desired location on the canvas. Hightlighted items are shown in red.
3. Tree View -> Shows the sketched items. Selectable items. Onca selected, the otem is hightlighted on the canvas in red colour. Can select 3 at a time. 
             When multiple items are selected, it also hightlights their intersection points.

Classes->
1. Main Window -> Consists of buttons and grids. Slots and connections. Cosmetics.
2. OpenGL Widget Handler -> Consists of all the required conversions for opneGL fixed pipeline. Functions that translate mouse clicks to desired shapes (Calculcations).
3. Database -> Central database. 
4. QT Window -> Displays QT Window
