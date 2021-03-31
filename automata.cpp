#include <iostream>
#include "automata.h"

using namespace std;

/**
 * Constructor for Abstract DFA.
 * 
 * @param noStates
 *            Number of states in the DFA.
 */
AbstractDFA::AbstractDFA(int noStates) {
    // TODO: initialize data structures
    this->currentState = 0;

    for (int i = 0; i < noStates; i++) {
        State s = State();
        s.index = i;
        s.final = false;
        this->states[i] = s;
    }
}

/**
 * Reset the automaton to the initial state.
 */
void AbstractDFA::reset() {
    // TODO: reset automaton to initial state
    this->currentState = 0;
}

/**
 * Performs one step of the DFA for a given letter. If there is a transition
 * for the given letter, then the automaton proceeds to the successor state.
 * Otherwise it goes to the sink state. By construction it will stay in the
 * sink for every input letter.
 * 
 * @param letter
 *            The current input.
 */
void AbstractDFA::doStep(char letter) {
    // TODO: do step by going to the next state according to the current
    if (this->currentState < 0)
        return;

    State s = this->states[this->currentState];
    if (s.nexts.count(letter)) {
        this->currentState = s.nexts[letter];
    } else {
        this->currentState = -1;
    }

    // state and the read letter.
}

/**
 * Check if the automaton is currently accepting.
 * 
 * @return True, if the automaton is currently in the accepting state.
 */
bool AbstractDFA::isAccepting() {
    // TODO: return if the current state is accepting
    if (currentState < 0)
        return false;
    return this->states[this->currentState].final;
}

/**
 * Run the DFA on the input.
 * 
 * @param inputWord
 *            stream that contains the input word
 * @return True, if if the word is accepted by this automaton
 */
bool AbstractDFA::run(const string &inputWord) {
    this->reset();
    for(int i = 0; i < inputWord.length(); i++) {
        doStep(inputWord[i]);
    }
    return isAccepting();
}


/**
 * Construct a new DFA that recognizes exactly the given word. Given a word
 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
 * from every state (including the final one) every other input letter leads
 * to a distinguished sink state in which the automaton then remains
 * 
 * @param word
 *            A String that the automaton should recognize
 */
WordDFA::WordDFA(const string &word) : AbstractDFA(0) {
    // TODO: fill in correct number of states
    
    // TODO: build DFA recognizing the given word

    State prec = State();
    prec.final = false;
    this->states.push_back(prec);

    for (int i = 0; i < word.length(); i++) {
        State next = State();
        next.final = false;
        prec.nexts[word[i]] = i;
        this->states.push_back(next);
        prec = next;
    }
    prec.final = true;
}
//CIAO
/**
 * Construct a new DFA that recognizes comments within source code. There
 * are three kinds of comments: single line comment that starts with // and ends
 * with a newline, multiline comments that starts with (* and ends with *), and
 * multiline comments that starts with { and ends with }
 */
CommentDFA::CommentDFA() : AbstractDFA(0) {
    // TODO: fill in correct number of states
    // TODO: build DFA recognizing comments
}

/**
 * Performs one step of the DFA for a given letter. This method works
 * differently than in the superclass AbstractDFA.
 * 
 * @param letter
 *            The current input.
 */
void CommentDFA::doStep(char letter) {
    // TODO: implement accordingly
}	


