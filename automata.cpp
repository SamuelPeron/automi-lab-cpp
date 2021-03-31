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
    if (s.nexts.find(letter) == s.nexts.end()) {
        this->currentState = -1;
    } else {
        this->currentState = s.nexts[letter];
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

    for (int i = 0; i < word.length(); i++) {
        State next = State();
        next.final = false;
        prec.nexts[word[i]] = i + 1;
        this->states.push_back(prec);
        prec = next;
    }
    prec.final = true;
    this->states.push_back(prec);

}
/**
 * Construct a new DFA that recognizes comments within source code. There
 * are three kinds of comments: single line comment that starts with // and ends
 * with a newline, multiline comments that starts with (* and ends with *), and
 * multiline comments that starts with { and ends with }
 */
CommentDFA::CommentDFA() : AbstractDFA(0) {
    // TODO: fill in correct number of states
    // TODO: build DFA recognizing comments

    State q0 = State();
    q0.final = false;
    q0.nexts['/'] = 1;
    q0.nexts['{'] = 4;
    q0.nexts['('] = 6;
    this->states.push_back(q0);


    // Comment //
    State q1 = State();
    q1.final = false;
    q1.nexts['/'] = 2;
    this->states.push_back(q1);

    State q2 = State();
    q2.final = false;
    q2.nexts['/'] = 2;
    q2.nexts['('] = 2;
    q2.nexts[')'] = 2;
    q2.nexts['*'] = 2;
    q2.nexts['{'] = 2;
    q2.nexts['}'] = 2;
    q2.nexts['#'] = 2;
    q2.nexts['\n'] = 3;
    this->states.push_back(q2);

    State q3 = State();
    q3.final = true;
    this->states.push_back(q3); 

    // Comment { }
    State q4 = State();
    q4.final = false;
    q4.nexts['/'] = 4;
    q4.nexts['('] = 4;
    q4.nexts[')'] = 4;
    q4.nexts['*'] = 4;
    q4.nexts['{'] = 4;
    q4.nexts['#'] = 4;
    q4.nexts['\n'] = 4;
    q4.nexts['}'] = 5;
    this->states.push_back(q4);

    State q5 = State();
    q5.final = true;
    q5.nexts['{'] = 4;
    this->states.push_back(q5);


    // Comment (* *)
    State q6 = State();
    q6.final = false;
    q6.nexts['*'] = 7;
    this->states.push_back(q6);

    State q7 = State();
    q7.final = false;
    q7.nexts['/'] = 7;
    q7.nexts['('] = 7;
    q7.nexts[')'] = 7;
    q7.nexts['{'] = 7;
    q7.nexts['}'] = 7;
    q7.nexts['#'] = 7;
    q7.nexts['\n'] = 7;
    q7.nexts['*'] = 8;
    this->states.push_back(q7);

    State q8 = State();
    q8.final = false;
    q8.nexts['/'] = 7;
    q8.nexts['('] = 7;
    q8.nexts['{'] = 7;
    q8.nexts['}'] = 7;
    q8.nexts['#'] = 7;
    q8.nexts['\n'] = 7;
    q8.nexts['*'] = 8;
    q8.nexts[')'] = 9;
    this->states.push_back(q8);

    State q9 = State();
    q9.final = true;
    q9.nexts['('] = 10;
    this->states.push_back(q9);

    State q10 = State();
    q10.final = false;
    q10.nexts['*'] = 7;
    this->states.push_back(q10);

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
    if (
        letter != '/' &&
        letter != '(' &&
        letter != ')' &&
        letter != '*' &&
        letter != '{' &&
        letter != '}' &&
        letter != '\n'
        )
        letter = this->DEFAULT_CHAR;
    AbstractDFA::doStep(letter);
}


