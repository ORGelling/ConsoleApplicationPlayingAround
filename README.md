This is a console application I'm using to practice with C++. I am using it to properly handle creating 
objects and functions, datatypes, and dynamically allocating memory. 

This readme will also function as my design doc, explaining my goals for the program and what I intend 
to learn from it.

Currently I am working on a frontend, which means I have to rewrite the logic slightly to encapsulate it 
under one or multiple classes. I am using Qt for the frontend, but am also curious about SDL2/3, or 
using a web frontend. Both of these approaches will be useful for my future projects.

Some notes I am keeping:

Web Frontend (Modern Approach)<br/>
How:<br/>
•	Write the game logic as a C++ library. <br/>
•	Use Emscripten to compile the C++ to WebAssembly.<br/>
•	Build a web frontend (HTML/JS/CSS) that interacts with the C++ logic.<br/>
•	Use HTML buttons and images for UI.

How Would You Use SDL3 for a Card Game?<br/>
•	Window and Rendering:<br/>
    Use SDL3 to create a window and render 2D graphics (such as card images and buttons).<br/>
•	Image Loading:<br/>
    Use the SDL_image extension to load PNG/JPG images of cards.<br/>
•	Event Handling:<br/>
    Use SDL3's event system to handle mouse clicks, keyboard input, and window events.<br/>
•	Drawing Cards and Buttons:<br/>
    Draw card images at specific positions. Draw buttons as images or rectangles, and detect clicks.<br/>
•	Game Logic Integration:<br/>
    Connect your existing C++ game logic to the SDL3 event loop and rendering code.<br/>

Steps for SDL3:<br/>
•	Install SDL3 and SDL_image (via vcpkg, package manager, or from source).<br/>
•	Initialize SDL3 in the main() function.<br/>
•	Load card images (e.g., "images/2H.png", "images/AS.png").<br/>
•	Render cards and buttons using SDL_RenderCopy.<br/>
•	Handle user input (mouse clicks, etc.) to let users pick cards or press buttons.<br/>
•	Update the display as the game state changes.