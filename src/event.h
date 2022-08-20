#pragma once

class Event {

public:
    enum class Type {
        NIL, MOUSE, KEYBOARD
    };
    Type type() const;
    
protected:
    const Type _type;
    Event(Type type);
};
