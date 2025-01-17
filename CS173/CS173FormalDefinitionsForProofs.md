# CS 173 Formal Definitions for Proofs

**Rational Number**: A number $q$ is rational if it can be written as $q = \frac{m}{n} \text{, " m", } n \in \mathbb{Z} \wedge \neg \left(n | m\right)$

* Fraction should be in simplest term and $n$ and $m$ should share no factors
**Even Number**: A number $A$ if even if $\exists B \in \mathbb{Z} \text{, } 2 B = A$

**Odd Number**: A number $A$ if odd if $\exists B \in \mathbb{Z} \text{, } 2 B + 1 = A$

**Factors**: $\forall A \text{, " B ", " C in ZZ", } A$ is a factor of $B$ if $A C = B$

* Must be an integer multiplied by another integer to be a factor basically is what this means
* B is a multiple of A
* A divides B means A is a factor of B
**Even Factor Definition**: A number $A$ is even if $2 | A$

**Prime Number**: An integer $A \ge 2$ is prime if the only factors of $A$ are $\left\{1 , A\right\}$

**Composite Number**: An integer $A$ is composite if it is not prime

**Congruence Mod K**: If $\displaystyle{A}\equiv{B}\%{m},\exists{n},{A}={B}+{n}{m}$

* More complicated definition: If $k$ is any positive integer, two integers $a$ and $b$ are congruent mod $k$ if $k | \left(| a - b |\right)$
* Order you subtract the numbers doesn't matter I put the absolute value sign there
**Subset** ($\subseteq$): Set $A \subseteq B$  if $\forall x \in A \text{, } x \in B$

**Partition**: Set $P$ is a partition of set $A$ if:

* ${P}_{1} \cup {P}_{2} \cup {P}_{3} \ldots \cup {P}_{\text{len} \left(P\right)} = A$
* $\emptyset \notin P$
* $\forall {P}_{i} , {P}_{j} \in P , {P}_{i} \ne {P}_{j} \to {P}_{i} \cap {P}_{j} \equiv \emptyset$
  * ${P}_{1} \cap {P}_{2} \ldots \cap {P}_{n}$ should NOT be used in definition: It doesn't guarantee all sets are mutually exclusive
  * $\left\{1 , 2\right\} \cap \left\{2 , 3\right\} \cap \left\{3 , 4\right\} \equiv \emptyset$ will pass this test even when there is overlap of $3$ between some sets

**Function Formal Definition/Type Annotation**: $F : D \to C D$ where $D$ is the domain set and $C D$ is the co-domain set

* Notation that shows expected inputs and outputs (domains and co-domains/ranges) of a function
* Rule: $\forall d \in D , \exists c d \equiv F \left(A\right) , c d \in C D$: Every domain value must map to at least 1 co-domain value
* Example function $F : A \to P \left(A\right)$
  * $A$ is any set of values ,$P \left(A\right)$ is the power set of A

**Onto Function**: A function $f : A \to B$ is onto if:

* $\forall b \in B , \exists a \in A , f \left(a\right) \equiv b$

**One to One Function**: A function $f : A \to B$ is a one to one function if:

* $\forall x , y \in A , x \ne y \to f \left(x\right) \ne f \left(y\right)$
* Contrapositive (easier to use sometimes): $\forall x , y \in A , f \left(x\right) \equiv f \left(y\right) \to x \equiv y$

**Asymptotically Smaller Functions**: Function $f(x) \ll g(x)$ if ${\lim}_{x \to \infty} \frac{f \left(x\right)}{g \left(x\right)} = 0$

**Asymptotically Similar Functions**: Function $f \left(x\right) \approx g \left(x\right)$ if ${\lim}_{x \to \infty} \frac{f \left(x\right)}{g \left(x\right)} = c$ where $c \in \mathbb{R}$

**Big O**: Function $f \left(n\right) = O \left(g \left(n\right)\right) \iff \exists c , k \in \mathbb{R} , c > 0 \wedge k > 0 , 0 \le f \left(n\right) \le c g \left(n\right)$ for every $n \ge k$

* Functions will have positive outputs as they progress
* $\le$ type relation, similar to asymptotically smaller but allows for $\le$ and not just $<$
* $\Theta \left(g\right)$ is for $=$ only relation between functions
  * $f \left(n\right)$ is $\Theta \left(n\right)$ when $f \left(n\right)$ is $O \left(g \left(n\right)\right)$  and $g \left(n\right)$ is $O \left(f \left(n\right)\right)$
