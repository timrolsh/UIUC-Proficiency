# CS 173 Notes

## Clone Repo And Use Preview in VSCode. Github Markdown Render Doesn't Render Some Things Properly

## Chapters to Learn

## Exam Info

The student code does not allow you to take the CS 173 Proficiency Exam after taking CS 374 (or a more advanced theoretical CS course).

The website for the Fall 2023 offering of CS 173 has a current set of skills lists, lecture notes, and videos. Course websites for Spring 2019 and earlier have old hardcopy exams that you can use for practice. (We have since moved the exams online.)

The exam will include some free-response questions (e.g. proofs) which are manually graded, so it will take a few days for results to be available. Details will be posted here in August about how to enroll for the exam on Prairielearn and how to access a “Sandbox”
assessment with notes on how to format your free-response work (LaTeX is not required).

3 hours CBTF

USE THIS SITE TO STUDY: <https://courses.grainger.illinois.edu/cs173/fa2024/ALL-lectures/lectures.html>

use this site for other exams: <https://courses.grainger.illinois.edu/cs173/sp2019/A-lecture/Exams/index.html>

## Math Review

$\displaystyle\mathbb{Z}\text{, }\ \mathbb{Z}^{+}\text{, }\ \mathbb{Z}^ -{}$: The set of all integers, positive, negative integers, respectively

* Zero is in neither positive or negative sets

$\mathbb{R}$: The set of all real numbers

* ${\mathbb{R}}^{2}$: The real plane in 2D, meaning all tuples of $\left(\mathbb{R} , \mathbb{R}\right)$
* Example: $\exists \left(x , y\right) \in {\mathbb{R}}^{2} \text{, } {x}^{2} + {y}^{2} = 1$: Definition for unit circle

$\mathbb{Q}$: The set of all rational numbers

$\mathbb{C}$: The set of all complex numbers

$\displaystyle{\left(\begin{matrix}{n}\\{k}\end{matrix}\right)}=\frac{{{n}!}}{{{k}!{\left({n}-{k}\right)}!}}$

Floor: The largest integer $\displaystyle{\left\lfloor{{3.75}}\right\rfloor}={3}$, $\displaystyle{\left\lfloor{-{3.75}}\right\rfloor}=-{4}$
**Closed Form**: Finite length formula/expression/way to calculate something you would otherwise have to calculate iteratively or recursively

Finite geometric series formula: ${\sum}_{k = 0}^{n} {r}^{k} = \frac{{r}^{n + 1} - 1}{r - 1}$

* Closed form, expression for geometric series that isn't $r = 1$

Closed form of summation: ${\sum}_{i = 1}^{n} i = \frac{n \left(n + 1\right)}{2}$
$\epsilon$: empty string

Alphabet (A): The set of all characters that can be used to make strings

* ${A}^{\text{*}}$: The set of all finite length strings that can be made from a character

**Regular Expressions**: Notation used to specify patterns for similar sets of strings

* $a | b$: either character a or b
* ${a}^{\text{*}}$: zero or more copies of character a

## Logic

$\wedge$: and
$\vee$: or
$\neg$: not
$\oplus$: xor, not equal, exclusive or, or but they cannot both be true, only one can be true
$p \equiv q$: Logically equivalent

* Easy to show non equivalent: Find one case that exists where same inputs to both $p$ and $q$ yield different boolean values
* Harder to show equivalence: You have to prove that all cases for in theory an entire truth table yield the same for both sides

**Logic Precedence**: $\displaystyle\neg\text{, }\ \wedge\text{, }\ \vee\text{, etc.}$

**Propositional Logic**: Logic based on propositions, which require a statement to be true or false, but not both

* No variables in propositional logic, statements must be explicit claims
* $x < 9$: invalid in propositional logic
**Predicate Logic**: Propositional logic but includes variables

**Commutative And/Or**:  $A \wedge B \equiv B \wedge A , A \vee B \equiv B \vee A$

### Conditionals Review

$p \to q = \neg p \vee q$: conditional, if p then q

* Notation: p is hypothesis, q is conclusion
$q \to p$: converse, not equivalent statements

$p \leftrightarrow q$: biconditional, $\left(p \to q\right) \wedge \left(q \to p\right)$

* If and only if concept

$\neg q \to \neg p$: contrapositive, $\neg q \to \neg p = p \to q$

**Demorgan's Laws**

* $\neg \left(p \vee q\right) \equiv \neg p \wedge \neg q$
* $\neg \left(p \wedge q\right) \equiv \neg p \vee \neg q$

**Distributive Property in Logic**

* $p \wedge \left(q \vee r\right) \equiv \left(p \wedge q\right) \vee \left(p \wedge r\right)$
* $p \vee \left(q \wedge r\right) \equiv \left(p \vee q\right) \wedge \left(p \vee r\right)$

**Quantifiers**: Tell you about how many entries in a set meet or should meet a condition

* $\forall$: for all
* $\exists$: There exists
  * $\forall$ and $\exists$ usually negate each other, an existential statement can be used to disprove a universal statement and vise versa
  * Some, at least one, etc. are all keywords for $\exists$
* $\exists!$: There exists unique, only one
* $\in$: is in
* Transforming quantifier statements: $\forall x \text{, } y \to z$
  * Contrapositive: $\forall x \text{, } \neg z \to \neg y$
  * quantifier stays the same
* Negation: $\neg \forall x \text{, " p -= EE x", } \neg p$, $\neg \exists x \text{, " p -= AA x", } \neg p$

**Nested Quantifiers ($\forall a , \exists b , c$)**:

* Order matters

## Proofs

proof by contrapositive, proof by induction, proof by contradiction

### Direct Proofs

* For proving $\forall x \in A \text{, } P \left(x\right)$, pick representative value for $x$
* Definitions defined with if are designed to work both ways
* This definition and the if in this context can be read both ways
* Try and put claim into conditional form, this is the easiest to prove
  * Once proof is in $p \to q$ form, start with assuming p, then proving q
  * For algebra work, work backwards is easier
* Even definition: $n \in \mathbb{Z}$ is even if $\exists m \in \mathbb{Z} \text{, } n = 2 m$
* Odd definition: $n \in \mathbb{Z}$ is odd if $\exists m \in \mathbb{Z} \text{, } n = 2 m + 1$

**Outline**:

* Start from variable declarations and hypothesis
* Move to information that needs to be proved

**Proof of Cases**: When you're proving a logical statement that involves $\vee$, do a subproof for each statement separated by the $\vee$

**Example #1**:

* Claim: If $q$ is rational, $2 q$ will also be rational
* Proof: Let $q$ be a rational number. We know that $q = \frac{m}{n}$ where $m \text{, } n \in \mathbb{Z}$ by the definition of a rational number. $2 m$ is an integer as 2 is an integer, and multiplying 2 integers gives you an integer. $2 q = \frac{2 m}{n}$, and since both the numerator and denominator are integers, $2 q$ will be a rational number as it is the ratio of two integers.

**Example #2**:

Claim: $\forall x \in \mathbb{Z}$ where $x$ is odd, ${x}^{2}$ will also be odd

Proof:

$x \in \mathbb{Z}$ is odd if  $\exists m \in \mathbb{Z} \text{, } x = 2 m + 1$ by the definition of an odd number.

$x = 2 m + 1 \text{, } {x}^{2} = {\left(2 m + 1\right)}^{2} = 4 {m}^{2} + 4 m + 1 = 2 \left(2 {m}^{2} + 2 m\right) + 1$.

We know that $2 {m}^{2} + 2 m$ will be an integer because m is an integer and integer operations are being performed on it. Therefore, $\exists o \in \mathbb{Z} \text{, } o = 2 {m}^{2} + 2 m$. Therefore, ${x}^{2} = 2 o + 1$, and ${x}^{2}$ is an odd integer.

### Examples/Counter Examples

Prove $\forall$ (universal statement): General proof

Prove $\neg \forall$: Use $\exists$ counter example

Prove $\exists$ (existential statement): Give an example

Prove $\neg \exists$: Use a $\forall$ proof

**Example 3**: Claim: $\exists x \in \mathbb{Z} \text{, } {x}^{2} = 0$
Proof:
$0$ is such a number. ${0}^{2} = 0$. So the statement is true.

* You can use concrete example for existential proofs, don't have to do general value

**Example 4**: Claim: Every rational number $q$ has a multiplicative inverse.

Proof: Take an example of a rational number $q = \frac{0}{1}$ made up of a ratio of two integers. The multiplicative inverse of $q$, $r$ is a value such that $q r = 1$. Because $q = \frac{0}{1} = 0 \text{, } 0 \times A = 0 \forall A \in \mathbb{R}$, $q$ is a counter example of at least one rational number that does have a multiplicative inverse. This claim is therefore false.

### Proof By Contrapositive

* Quantifier $p \to q$ goes to Quantifier $\neg q \to \neg p$
* Different from negating quantifiers, quantifier stays the same because the expression remains logically equivalent
* When you have an original conditional statement claiming that something does not exist, for instance, $p \to A \equiv \emptyset$, contrapositive works well to negate that, instead working with if you have the existence of something

### Proof by Induction

* Based on recursive idea, you have a base case and you prove that it recursively works with inductive step
Layout:
* Claim: For all $n , b \in \mathbb{Z}$ where $n \ge b , P \left(n\right)$.
* Proof: By induction on $n$.
* Base case: Prove that $P \left(b\right)$ is true where $b$ is base case value
* Inductive hypothesis (in this example): Suppose $P \left(n\right)$ is true for $n = b , \ldots , k$
  * $k$ is some arbitrary fixed value, you want to prove that claim will work for not only $n = k$, but $n = k + 1$ as well
* Inductive step: If $P \left(n\right)$ is true for $n = b , \ldots , k ,$ then $P \left(k + 1\right)$ is also true
  * Evaluate one expression until it lines up with other one, like you would for trig proof
* Tips: Break up/combine summations and exponents just like in calc ratio/root test simplifications

### Proof by Contradiction

* Claim: $P : \sqrt{2}$ is not rational
* Proof: Suppose $\neg P , \sqrt{2}$ is rational
* A rational number is defined by $\frac{A}{B} , A , B \in \mathbb{Z} , \neg \left(B | A\right)$
* A number $n$ is even iff ${n}^{2}$ is even
* If $n = \sqrt{2} = \frac{A}{B} , {n}^{2} = {\sqrt{2}}^{2} = 2 = \frac{{A}^{2}}{B} ^ 2 , {A}^{2} = 2 {B}^{2}$
* Therefore, $A , B$ are even, meaning $\exists n , m \in \mathbb{Z} , 2 n = A , 2 m = B$
* Because $A , B$ are even, they share a common factor of $2$, which is a contradiction to definition of rational number
* False statement. Therefore we proved that this is false.

## Number Theory

**Number Theory**: Branch of mathematics focused on behavior of integers

* Applications to cryptography, algorithms for randomization
* Common questions are which integers divide evenly, which integers are prime, etc.

**Factor Notation**: A divides B or A is a factor of B is written as $A | B$
Tip: Avoid using $\frac{B}{A}$ and putting factors into ratios unless you have to, just use multiplication instead to avoid making the problem more complex

**Notation for greatest common divisor**: $\text{gcd} \left(a , b\right)$

**Relatively Prime**: Two numbers that share no common factors, $\text{gcd} \left(a , b\right) = 1$

### Euclid's GCD Algorithm

* First you take the theorem that $\text{gcd"(a,b) = "gcd} \left(b , r\right)$ for division algorithm
* Recursively apply this problem (your $b \text{, } r$ output becomes the next $a \text{, } b$ input so you can get the next $b \text{, } r$ pair) until you hit your base case of $r = 0$

```python
"""
Iterative Implementation
Probably faster on most architectures cause no call stack and return address overhead
Copied by value into function, b can be modified
"""
def gcd(a: int, b: int) -> int:
 r: int = a % b
 while r != 0:
  new_remainder: int = b % r
  b = r
  r = new_remainder
 # at this point b will be gcd and r will be 0, gcd(b,0) will be b base case reached
 return b

"Recursive Implementation"
def gcd(a: int, b: int) -> int:
 r: int = a % b
 if r == 0:
  return b
 return gcd(b, r)
```

**Congruence Mod K**: Foundation for modular arithmetic, idea that two numbers yield the same result when they are modded by the same modulus

* Notation: $13 \equiv 8 \text{ mod} \left(5\right)$

**Congruence/Equivalence Classes**: Sets of numbers that are all congruent mod the same modulus k

* Example: If $k = 7 \text{, } \left[3\right] = \left\{10 , 17 , 3 , \ldots\right\}$
* Equivalence classes $\left[a\right]$ can be numbered any number, goal is to get $a$ down to $a < k$, you can perform operations on these sets
* $\left[x\right] + \left[y\right] = \left[x + y\right]$

**Modular Arithmetic**: You can perform mod on values before you operate on them to decrease number size, helps avoid overflow, used in quadmod and factor

* Multiplication: $\displaystyle{\left({A}{B}\right)}\%{C}={\left[{\left({A}\%{C}\right)}{\left({B}\%{C}\right)}\right]}\%{C}$
* Addition: $\displaystyle{\left({A}+{B}\right)}\%{C}={\left[{\left({A}\%{C}\right)}+{\left({B}\%{C}\right)}\right]}\%{C}$
* Notation: ${\mathbb{Z}}_{A}$ means $\displaystyle{\left\lbrace{x}\%{A}\ \text{ }\ \forall{x}\in\mathbb{Z}\right\rbrace}\equiv{\left[{0},{A}-{1}\right]}$
  * Anything arithmetic that takes place inside of ${\mathbb{Z}}_{n}$ is modular arithmetic
  * $\left\{y \in {\mathbb{Z}}_{n} | {y}^{2} = x\right\}$ means $\displaystyle{y}^{2}\%{n}={x}$

## Sets

**Set**: Unordered collection of objects

* Each element in a set is unique
* Different from a tuple because tuples are

**Empty Set** ($\left\{\right\} \text{, } \emptyset$): Set with no elements in it

**Subset** ($A \subseteq B$): $B$ contains all of the elements that $A$, $A \subseteq A$ always for any set $A$

* $\emptyset \subseteq A$ where $A$ is any set

**Proper Subset** ($A \subset B$): $A \subseteq B \wedge A \ne B$

**Superset/Proper Superset**: $\supseteq \text{, } \supset$ and the opposite of subset

**Disjoint Sets**: Sets $A$ and $B$ are disjoint if $A \cap B \equiv \emptyset$

**Set Subtraction** ($A - B$): Everything in $A$ that isn't in $B$

**Universal Set** ($U$): Set that will contain all elements of all sets for the context of a problem

* Example: You're working in a number theory problem involving only integers $\to$ $U \equiv \mathbb{Z}$

**Complement Set** ($\overline{A}$): Everything in $U$ but not in $A$, or $U - A$

* Negation idea in set theory

**Cartesian Product** ($A \times B$): $\left\{\left(x , y\right) | x \in A \text{, } y \in B\right\}$

* Every combination of elements of A and B put together
* $A \times B \ne B \times A$ for sets $A$ and $B$, order matters
* Example: $A = \left\{1 , 2\right\} \text{, } B = \left\{a , b\right\}$
  * $A \times B = \left\{\begin{matrix}1  &  a  \\  1  &  b  \\  2  &  a  \\  2  &  b\end{matrix}\right\}$
  * $B \times A = \left\{\begin{matrix}a  &  1  \\  a  &  2  \\  b  &  1  \\  b  &  2\end{matrix}\right\}$
  * Tuple $\left(2 , a\right) \ne \left(a , 2\right)$
  
**Cardinality** ($| A |$): The number of elements in a finite set $A$

* $| A \times B | = | A | | B |$
* $| A \cup B | = | A | + | B | - | A \cap B |$
  * Inclusion-exclusion principle
  
**Tuple**: Ordered list of elements that must be at least length 2 and
can have duplicates

* $\left\{\right\}$ notation for sets and $\left(\right)$ notation for tuples just like in python

**Set Builder Notation**: Build sets sometimes of infinite size

* All integers between 3 and 7 inclusive: $\left\{x \in \mathbb{Z} | 3 \le x \le 7\right\}$
* $|$ or $:$ used as such that in this case, generally best to use :
* $x \in \mathbb{Z} : 7 | x$: all multiples of 7, $|$ in this case is used to show factor

**Set Subtraction**: $A - B$ means drop $A \cap B$ form $A$

## Set Collections

**Collection**: A set contained of sets

**Power Set** ( $P \left(A\right)$): Set that contains all the possible subsets of set $A$
Subsets of set $A$ of length $m$ contain $n$ elements? : $\displaystyle{\left(\begin{matrix}{m}\\{n}\end{matrix}\right)}=\frac{{{m}!}}{{{\left({n}!\right)}{\left({m}-{n}\right)}!}}$ because order in sets doesn't matter, for tuples it does matter

**Combinations with Repetition**: Cases where you have set  of size $n$, can put multiple copies of the same element in a new set of a certain size $m$, which can be larger than the set you're pulling from, $m > n$

* All combinations is $\left(\begin{matrix}m + n - 1  \\  n - 1\end{matrix}\right)$ , think of $n - 1$ as dividers for sections of duplicates
* Dividers can be right next to each other for empty sections, entry from set $n$ was not used

 **Partition**: Process of dividing a set of elements into a set of subsets containing those elements, grouping elements together in a se t

* Partitioning a drive means to take the set of all of its storage and make subsets (partitions) of those storage areas on the entire drive
* Sets of a partition will be an entries in the power set
* Partition should cover all elements of the base set, no overlap between elements, no empty set

## Functions

* Functions have input (domain) defined for sets, and output (co-domain, range, a set of possible outputs), these can be used as type signatures
* Input to a function taking in a set $A$ will be $P \left(A\right)$, output can be any value of $P \left(A\right)$
  * Functions that takes subsets of sets will usually have their range be $P \left(A\right)$ as $P \left(A\right)$ is all possible subsets a set $A$ can have
* Every value from domain must map to somewhere in co-domain in a function

**Onto function**: Every element in the co-domain has an input in the domain that maps to it (requirement for function to be reversed)

**Image**: Set of all possible actual outputs of a function

* Onto functions means that for set $A , \text{Image"(A) -= "Co-Domain} \left(A\right)$
* Function can have multiple images, called **pre-images**

### Onto Proof

Claim: function $F : {\mathbb{Z}}^{2} \to Z , F \left(x , y\right) = 2 x + 3 y$ is an onto function

1. Invert the function, ${F}^{- 1} : Z \to {\mathbb{Z}}^{2} , {F}^{- 1} \left(a\right) = \left(- a , a\right)$. To get ${F}^{-} 1$, you can solve this system: $2 x + 3 y = a , x + y = 0$
2. $\left(- a , a\right) \in {\mathbb{Z}}^{2}$ is a pre-image of of $F$ because $F \left(- a , a\right) = - 2 a + 3 a = a$
3. Therefore, $f$ is onto because every value $a$ has a pre-image.

**One to one**: Every element in the domain must only map to one output in the co-domain (also requirement for function to be reversed)

### One to one Proof

Claim: Function $\displaystyle{g}:\mathbb{Z}\to\mathbb{Z}\ \text{ is a one to one function. }\ {f}:\mathbb{Z}\to\mathbb{Z}^{2}, f{{\left({x}\right)}}={\left( g{{\left({x}\right)}}{\left|{x}\right|},{\left|{x}\right|}\right)}\text{. Prove }\ {f}\ \text{ is a one to one function.}$

1. Let $A , B \in \mathbb{Z} . \text{ Suppose " f(A) -= f(B), (g(A)|A|,|A|) = (g(B)|B|,|B|) " by definiton of } f .$
2. $g \left(A\right) | A | = g \left(B\right) | B | , | A | = | B |$
3. $g \left(A\right) = g \left(B\right) \text{ when } A \ne 0 , B \ne 0$, and $g$ is a one to one function, so that makes the tuple one to one for all of those cases.
4. $\text{When } A = 0 , B = 0 , A = B , f \left(A\right) \equiv f \left(B\right) \equiv \left(0 , 0\right) .$

So in all cases, $A = b$ and the proof by contrapositive works out.

**Pigeonhole Principle**: If you have more variables than values, labels then objects, etc. etc., then some variables are going to have to have the same value

* You know at least two variables are sharing the same value, but you don't know the details of how its organized*

## Graphs

**Isomorphic**: Idea that two graphs have same amount of vertices and edges and are connected to each other same way, and that the shapes of graphs doesn't matter, they are still mathematically the same

* Count the amount of edges connecting to vertices to identify vertices between different graphs, start with most connecting edges

**Degree**: If a node/vertex has a degree of $n$, it has $n$ connecting edges to it

**Bipartite**: Ability to split vertices of a graph into 2 sets $A , B$ such every edge moves from $A$ to $B$, nothing connecting vertices within those sets themselves

**Counting Isomorphisms**: Calculating how many ways you can re-arrange the variables/lables for the nodes and how many nodes are essentially the same

**Lower Bound**: Any quantity lower than the quantity you are trying to estimate

**Higher Bound**: Any quantity higher than the quantity you are trying to estimate

* Ideally you want these values to be as close to the estimate as possible to give you a reasonable idea of what the estimate can be

**Complete Graph $\left({K}_{n}\right)$**: Graph where every vertex is connected to all other vertices in the graph

* Number of edges in a complete graph: $\left(\begin{matrix}n  \\  2\end{matrix}\right)$

**Graph Coloring**: Each node has a color, adjacent nodes connected directly by an edge must have different colors

* ${K}_{n}$ complete graphs require $n$ colors
* Bipartite graphs can be colored with 2 colors
* Even circular graphs need 2 colors, odd circular graphs need 3, 1 extra to avoid direct edge same color
  * Wheels (vertex in the middle of the wheel) requires one more color

## Recursive Definitions

* Problems consist of finding closed forms of recursive functions to then do induction on them, proving that the recursive method $=$ the closed form method for the next iteration of $n = k , i . e . n = k + 1 , n = 2 k$, etc.
* They will usually give you a recursive function with a base case, then have you derive the

## Recursion Trees

* Makes finding closed forms of recursive definitions easier than simple unrolling/factoring technique
* Root node of a tree is at level $0$, but a tree with only one node has 1 level, done the same way as array indices and array length

**Full Binary Tree**: Tree such that every node has either $2$ children or $0$ children
Sample function: $A : \left\{{2}^{m} \text{ } \forall m \in \mathbb{N}\right\} \to \mathbb{N} , A \left(4\right) = c , A \left(n\right) = 4 A \left(\frac{n}{2}\right) + \mathrm{dn}$

* Problem Size at Leaf Level: 4 from $A \left(4\right) , 4$ is base case problem size
  * Base case is the leaves of the tree, when it stops recursing
  * Solve for which level $k$ will leaf level size be hit given input $n$
  * $\frac{n}{2} ^ k = 4 = {2}^{2} , n = {2}^{k + 2} , k = {\log}_{2} \left(n\right) - 2$
* Number of subproblems/Branching Factor: 4 from $4 A$
  * At level 1 in this example, $4$ subproblems, level $2 , 16$ subproblems total, level $k , {4}^{k}$ subproblems
* Input size: $n$
* Subproblem size for next level: $\frac{n}{2}$
  * At level $k$, total subproblem size is $\frac{n}{2} ^ k$
* Work at each leaf: $c$, will usually be a constant
* Extra work: $\mathrm{dn}$
  * Work you do to setup the recursive calls, combine the results of recursive calls, etc.
  * On level 1 in this example, you will have $\frac{\mathrm{dn}}{2}$ extra work to do per node, level 2 will be $\frac{\mathrm{dn}}{4}$, level $k$ is $\frac{\mathrm{dn}}{2} ^ k$
* At level $k$ in the tree: $\text{Work at each level" = "Total subproblems at level" xx "Extra work per node} = {4}^{k} \times \frac{\mathrm{dn}}{2} ^ k = {2}^{k} \mathrm{dn}$  for this example
* $\text{Total Work Done in Recursion} = {\sum}_{k = 0}^{{\log}_{2} \left(n\right) - 2 - 1} {2}^{k} \mathrm{dn} = \mathrm{dn} {\sum}_{k = 0}^{{\log}_{2} \left(n\right) - 2 - 1} {2}^{k} = \mathrm{dn} \left(\frac{{2}^{{\log}_{2} \left(n\right) - 2 - 1 + 1} - 1}{2 - 1}\right) = \mathrm{dn} \left(\frac{n}{4}\right) = \frac{{\mathrm{dn}}^{2}}{4}$
  * For last $k$ layer before bast case
* $\text{Total Leaf Node Constant Base Case Value} = {4}^{{\log}_{2} \left(n\right) - 2} \times c = \frac{{n}^{2} c}{16}$
* Final closed form: $A \left(n\right) = \frac{{\mathrm{dn}}^{2}}{4} + \frac{{n}^{2} c}{16}$

**Tree Grammar**: Definition for what the values of nodes can be

* $A \to B C$ means any node with label $A$ (start symbol) can have left child $B$ and right child $C$ (end symbols)
* Grammar trees can sometimes be of height 1 if start symbol set does not allow for no input/null, height of $h = 1$ will therefore be your base case

### Recursion/Grammar Tree Inductive Proofs

* Divide trees into the subtrees that are the children of the root node, do this recursively
* You can do induction on height $h$, use height of $h = k - 1$
* You can apply the inductive hypothesis on the subtrees, for instance, if IH is "Suppose tree $T$ is a llama tree", then subtrees ${T}_{1} , {T}_{2}$ can also be assumed to be llama trees
  * Divide the tree at the root and recursively do this, in this case $T$, the root tree, is the one being divided

## Time Complexity Review

**Wiggling in functions**: Large changes in runtime throughout function input size increase instead of consistent trend

**Evaluating $O \left(n\right)$ for polynomials**

* $k = 1$ is a good starting point, but when you have $\log \left(n\right)$ functions choose $k$ values carefully
* To find a safe goal for c$c$, raise all terms to the fastest growing term and combine them, i.e $f \left(n\right) = 2 {n}^{2} + 3 n + 7 \to 2 {n}^{2} + 3 {n}^{2} + 7 {n}^{2} = 12 {n}^{2} \to \text{goal} = 12$
* If $g \left(n\right) = 2 {n}^{2} + n$, this is the larger function, coefficient of most significant growing term is $2 \to \frac{12}{2} = 6 \to c = 6$

**Polynomial Time**: Any time $O \left(n\right) = {n}^{k}$ where $k$ is a constant is polynomial

**Exponential Time**: Any time $O \left(n\right) = {k}^{n}$ where $k$ is a constant is exponential

**Nondeterministic Polynomial (NP) Time**: Solution can be verified in polynomial time (this is the only requirement)

* Solving the problem may not be polynomial time, can be exponential or something else

**Ordering Of Functions**: $\displaystyle{1}\to{{\log}_{{c}}{\left({n}\right)}}\to{n}\to{n}{{\log}_{{c}}{\left({n}\right)}}\to{n}^{c}\to{n}^{{{c}+{1}}}\to{c}^{n}\to{\left({c}+{1}\right)}^{n}\to{n}!$

* $c$ is a constant, does not matter in log bases for $O \left(n\right)$ comparison purposes, but has an impact in exponents and exponent bases

**Dominant Method Function Comparison**: To compare functions, pick out the most dominant method and compare the using the ordering of functions

### Code Runtime Analysis

* Pay attention to nested loops, while loops, and recursive function calls
* Make a formula and make a recursion tree for that formula

## State Diagrams/FSAs Review

* FSM is a graph where vertices are states and edges are actions that you take to get from one state to another, it is typically a directed graph
* You have one start state but can have multiple end/accept states (accept states have double circle)
* You feed characters in, one per transition
Determinism: Idea that if you have vertices $A , B$ and transition $T$ between them, $\displaystyle\exists!{T}$ that goes from $A$ to $B$, you can always know where the transition will take you
* DFAs go deterministic, NFAs split into parallel threads when the same transition leads to more than 1 resulting node

## Countability

* Process of comparing the sizes of infinite sets
* $| A | \le | B | \iff \exists$ one to one function $f : A \to B$

**Bijection**: Function that if it exists, sets of infinite size are considered to be the same size, $| A | = | B |$

* Example bijection function for $\mathbb{N} \to \mathbb{Z} , f \left(n\right) = \frac{n}{2} \text{ if n is even", f(n) = -(n+1)/2 " if n is odd}$

**Countably Infinite Set**: Set that can be mapped, has the same size as $\mathbb{N} , \mathbb{Z}$

**Countable Set**: Set that is either finite, or infinite by countably infinite and can be mapped

**Alternative to Bijection**: If $| A | \le | B | \wedge | B | \le | A | \to | A | = | B |$

* Easier than using bijection because you just make 2 one to one functions for both directions
* Easy way to go from ${\mathbb{N}}^{2} \to \mathbb{N} : F \left(A , B\right) = {2}^{A} {3}^{B}$
* Numbers to characters: Make 1 number for the number of As or something, 1 is A, 2 is AA, etc. that is one to one
* Characters to numbers: Use ascii table to generate numbers from characters
* Finite sets of strings are countable by this methods, many things can be set to finite sets of strings (DNA sequence, computer program, etc.)
