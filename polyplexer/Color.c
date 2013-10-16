#include "Color.h" 


// Macro pour empecher la coloration du terminal
// Permet d'eviter de polluer le terminal d'un systeme non compatible par exemple
#ifdef NCOLOR

void textcolor(int attr, int fg, int bg)
{}
void color_reset()
{}
void color_text(int fg)
{}


#else
void textcolor(int attr, int fg, int bg)
{
  char command[13];
  
  /* Command is the control command to the terminal */
  sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
  fprintf(stderr, "%s", command);
}

void color_reset()
{
  char command[13];
  sprintf(command, "%c[%dm", 0x1B, RESET);
  fprintf(stderr, "%s", command);
}
/**
 * Fonction simplifiée permetant de colorer le texte qui suit cette appel de fonction
 *
 * @param int fg : Couleur désirée pour le texte. Se reporter au #define des colores possible. 
 **/
void color_text(int fg)
{
  char command[13];
  sprintf(command, "%c[01;%dm", 0x1B, fg + 30);
  fprintf(stderr, "%s", command);
}
#endif
