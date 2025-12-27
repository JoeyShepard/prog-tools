#ifdef CG50

    #include <stdint.h>
    #include <gint/exc.h>

    #include "exceptions.h"

    volatile bool address_exception;

    static int handle_exception(uint32_t code)
    {
        if ((code==EXCEPTION_WADDERR)||(code==EXCEPTION_RADDERR))
        {
            gint_exc_skip(1);
            address_exception=true;
            return 0;
        }
        return 1;
    }

    void setup_exception_handling()
    {
        address_exception=false;
        gint_exc_catch(handle_exception);
    }


#endif
