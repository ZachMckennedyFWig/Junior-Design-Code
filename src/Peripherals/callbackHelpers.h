#ifndef CALLBACK_HELPERS_H
#define CALLBACK_HELPERS_H

namespace Clbk_Helpers
{
     /**
     * A helper null callback for when we don't want to 
     * assign a callback to an event
    */
    void nullClbkFunc();
} // namespace Clbk_Helpers

void Clbk_Helpers::nullClbkFunc() {
    
}

#endif