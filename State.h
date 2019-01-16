/*****************************
 * Project part B of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * Januar 2019
 ******************************/

#ifndef NEWPROJ_STATE_H
#define NEWPROJ_STATE_H

template<class T>
class State {
protected:
    T state;
    State<T> *cameFrom;
public:
    State(T state) : state(state) {}

    virtual void setCameFrom(State<T> *cameFrom) {
        this->cameFrom = cameFrom;
    }

    virtual T getState() const {
        return state;
    }

    virtual void setState(T state) {
        State::state = state;
    }
};

#endif //NEWPROJ_STATE_H
