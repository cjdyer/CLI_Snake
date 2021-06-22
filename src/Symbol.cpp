#include "../include/Symbol.h"

//╔
//╗
//╚
//╝
//═
//║
//^
//«
//»
//¥

const char* GetSymbol(const Head_Symbol sym)
{
    const char* symbol;
    switch(sym)
    {
       case Head_Symbol::LookUp:
            symbol = "^";
            
        case Head_Symbol::LookLeft:
            symbol = "«";
            
        case Head_Symbol::LookRight:
            symbol = "»";
            
        case Head_Symbol::LookDown:
            symbol = "¥";
    }
    return symbol;
}
const char* GetSymbol(const Body_Symbol sym)
{
    const char* symbol;
    switch(sym)
    {
        case Body_Symbol::TopLeft:
            symbol = "╔";
            
        case Body_Symbol::TopRight:
            symbol = "╗";
            
        case Body_Symbol::BottomLeft:
            symbol = "╚";
            
        case Body_Symbol::BottomRight:
            symbol = "╝";
            
        case Body_Symbol::Horizontal:
            symbol = "═";
            
        case Body_Symbol::Vertical:
            symbol = "║";
    }
    return symbol;
}
