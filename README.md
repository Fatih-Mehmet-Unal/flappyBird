# flappyBird


We used Qt Creator for this project. Serhat created the Scene class, Sümeyye found the necessary visual elements that we used and created the widget class ,
Yusuf created the BirdItem class,Fatih created the PillarItem class.
Here We explained Compilation and Execution of the Flappy Bird Project.

Compilation and Execution of the Flappy Bird Project:

Qt Installation: First, you need to install the Qt framework on your computer. You can download and install the appropriate version from the official Qt website.
Opening Qt Creator: Open Qt Creator to run the project.
Opening the Project: Use the "File" menu in Qt Creator and select "Open File or Project" to open the directory where the project is located. Choose the .pro file of the project.
Build and Run: Compile the project using the "Build" button at the bottom of Qt Creator and then run it with the "Run" button.
Game Controls:

Start Button: Click on the "Start" button on the interface to initiate the game.
Flying: Once the game starts, press the space key or click the left mouse button to make the bird fly upward.
Score: The score increases for each obstacle passed during the game.
Game Over: The game ends if the bird collides with obstacles. When the game ends, the "Game Over" screen is displayed, showing the score and the best score.

Code Structure and Functions:

BirdItem class: Contains the properties and animations of the bird.
PillarItem class: Represents obstacles and handles collision control with the bird.
Scene class: Manages the game scene, adds the bird and obstacles, and controls the game state.
Widget class: Contains the game interface and the start button.
Running the Game:

When the game starts, the bird and obstacles are displayed on the screen.
Use the space key or left mouse button to make the bird fly.
When the bird collides with obstacles, the game ends, and the "Game Over" screen is displayed.
The score and the best score are shown on the screen.

Points to Note:

Executable is named flappyBird and can be found in executable folder.
Ensure that the dependencies for compiling and running the project are correctly installed in Qt Creator.
The project files should be added and organized correctly.
Visual files required for the game to run smoothly should be in the appropriate locations.
By following these steps, you can compile and run the code, experiencing the basic controls of the game.
