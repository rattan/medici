#pragma once

class Event {
protected:
    enum class Type;
    const Type _type;
    Event(Type type);
public:
    enum class Type {
        NIL, MOUSE, KEYBOARD
    };
    Type type() const;
};
