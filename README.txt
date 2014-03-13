This is a small console game "Mines" written on C.
Compiled succesfully using Windows 7 / Visual Studio 2013

About this game:
 - After the game starts, the user can choose the number of mines and the game window size(it's a square).
 - Use arrows to move through the cells, the cursor will mark the current position. if the selected square is not empty, the value will blink.
 - Mark Mines with Space. If there is some number and the number of mines around that square is equal to the in it, you can press Enter -> to open the other squares (cells)
 - For additional infromation - press 'I' during game.
 
Controls:
 - arrows. Space, Enter

Config file:
 - should be in the same folder as project with name "config.cfg"
 - it contains:
Enable_H_button					1  // (0 or 1) This is help button - Show solutions with hidden mines
Enable_I_button					1  // (0 or 1) This is information Button - show controls and other information
Save_Records					1  // (0 or 1) This option allows users to save their results in a file. 
Records_filename				RecordList.txt  // Record file name if the above option is selected
MinimumWindowSize				2  //
MaximumWindowSize				9  // User can choose the Game Window size when the game starts, but the value should be in these constrains.
MinimumNumberOfMines				1
CheckForSolution_beforeEnter			1  // This option is checking if the correct solution is provided, before the user hit enter at the end of the game. If this option is set to '1' and last mine of the field is correctly selected, Congratulation message will appear.
hideKursor					1  
Dont_HIT_mines_withEnter			1
Show_nearestEmptySquaresMatrix			0