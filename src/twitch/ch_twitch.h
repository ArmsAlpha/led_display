/*IDEAS:
       - Display lines that scroll up every so often to emulate a scrolling chat
       - Initial line is random length and color to represent username
       - Possibility of random colored bit + empty bit to represent sub badge
       - SUbsequent lines are grey and can be random length/span multiple lines
       - Duration before scrolling is random but is a multiple of the time it takes for twitch chat to update
       - Scroll is achieved by moving contents of buffer up x lines depending on how many new chats are added
       
       - Make function drawMessage() which takes in parameters for lengths (name, message, etc.)
       */

      //Draw name of random length and color
      //(Random) Overwrite first 2 bits of name with a color followed by black
      //Decide how long the message will be
      //Start drawing message 2 spaces after name ends
      //>If message would reach the edge of the screen, move down a line and continue until counter is done
      //>While message is being drawn, have chance to replace bit with blank bit if there have been consecutive bits drawn
      //

      //!!!Have chance to draw chat reminder instead of message