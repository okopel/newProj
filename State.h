

#ifndef NEWPROJ_STATE_H
#define NEWPROJ_STATE_H


template<class T>
class State {
protected:
    T state;
    State<T> *cameFrom;
public:
    State(T state) : state(state) {}

    void setCameFrom(const State<T> &cameFrom) {
        State::cameFrom = cameFrom;
    }

    T getState() const {
        return state;
    }

    void setState(T state) {
        State::state = state;
    }
};

#endif //NEWPROJ_STATE_H
