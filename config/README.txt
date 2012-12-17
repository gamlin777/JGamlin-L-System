--------------------J Gamlin L-System Config Template--------------------
_________________________________________________________________________

---When editting the configuration files ("exampleNUM.txt") please follow this format:

Line 1: Number of iterations (plant growth stages)(No decimal point)
Line 2: Branching angle value (Always use decimal point)
Line 3: The Axiom (Origin)
Line 4: Production Rule 1
Line 5: Node (Secondary Axiom)
Line 6: Production Rule 2



---The list of production rules:

F = Forward one step (Draws Line
f = Forward one step (Doesn't Draw Line)
X = Forward one step (Draws Line)
x = Forward one step (Doesn't Draw Line)
+ = Increase Angle
- = Decrease Angle
[ = Pushes Stack (Starts a branch)
] = Pops Stack (Ends a branch)

n/b if you DO NOT want a Node or Second Production Rule, please use: 'empty'