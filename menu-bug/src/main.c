#include <gint/display.h>
#include <gint/gint.h>
#include <gint/keyboard.h>

#include <stdbool.h>

#define GETKEY_ARGS     (GETKEY_DEFAULT & ~GETKEY_MENU)

int main(void)
{
    char counter=0;
    char *text="X. Sample fxSDK add-in.";
    bool gint_osmenu_ran=false;
    bool gint_poweroff_ran=false;
    

    while(1)
    {
        dclear(C_WHITE);

        //One digit counter to show program hasn't crashed
        counter++;
        counter%=10;
        text[0]=counter+'0';
        dtext(1, 1, C_BLACK, text);

        //Show whether functions ran or MENU and ACON handled automatically
        if (gint_osmenu_ran) dtext(1,16,C_BLACK,"gint_osmenu ran");
        if (gint_poweroff_ran) dtext(1,31,C_BLACK,"gint_poweroff ran");
        gint_osmenu_ran=false;
        gint_poweroff_ran=false;

        dupdate();

        key_event_t e=getkey_opt(GETKEY_ARGS,NULL);
        if (e.type==KEYEV_DOWN)
        {
            if (e.key==KEY_MENU)
            {   
                //Save state here if necessary
                gint_osmenu(); 
                gint_osmenu_ran=true;
            }
            else if (e.key==KEY_ACON)
            {
                //Save state here if necessary
                gint_poweroff(true); 
                gint_poweroff_ran=true;
            }
        }
    }
}
