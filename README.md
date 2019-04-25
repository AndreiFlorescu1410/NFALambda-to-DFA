# λ-NFA to DFA

## Deterministic Finite Automata (DFA)  
DFA is a finite automata where, for all cases, when a single input is given to a single state, the machine goes to a single state, i.e., all the moves of the machine can be uniquely determined by the present state and the present input symbol.

## Non-determinestic Finite Automata (NFA)  
NFA is a finite automaton where for some cases when a single input is given to a single state, the machine goes to more than 1 states, i.e. some of the moves cannot be uniquely determined by the present state and the present input symbol.

## Steps to Convert NFA with λ-move to DFA :  
1. Take λ closure for the beginning state of NFA as beginning state of DFA.  
2. Find the states that can be traversed from the present for each input symbol  
(union of transition value and their closures for each states of NFA present in current state of DFA).  
3. If any new state is found take it as current state and repeat step 2.  
4. Do repeat Step 2 and Step 3 until no new state present in DFA transition table.   
5. Mark the states of DFA which contains final state of NFA as final states of DFA.  

More info at [GeeksForGeeks](https://www.geeksforgeeks.org/program-implement-nfa-epsilon-move-dfa-conversion/).
