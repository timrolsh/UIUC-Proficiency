# CS 173 Formal Definitions for Proofs

**Rational Number**: A number `$q$` is rational if it can be written as `$q = m/n", " m", " n in ZZ ^^ not (n | m)$`

* Fraction should be in simplest term and `$n$` and `$m$` should share no factors
**Even Number**: A number `$A$` if even if `$EE B in ZZ", " 2B = A$`

**Odd Number**: A number `$A$` if odd if `$EE B in ZZ", " 2B + 1 = A$`

**Factors**: `$AA A", " B ", " C in ZZ", " A$` is a factor of `$B$` if `$AC = B$`

* Must be an integer multiplied by another integer to be a factor basically is what this means
* B is a multiple of A
* A divides B means A is a factor of B
**Even Factor Definition**: A number `$A$` is even if `$2 | A$`

**Prime Number**: An integer `$A >=2$` is prime if the only factors of `$A$` are `${1, A}$`

**Composite Number**: An integer `$A$` is composite if it is not prime

**Congruence Mod K**: If `$A -= B " " % " " m, EE n, A = B + nm$`

* More complicated definition: If `$k$` is any positive integer, two integers `$a$` and `$b$` are congruent mod `$k$` if `$k | (|a-b|)$`
* Order you subtract the numbers doesn't matter I put the absolute value sign there
**Subset** (`$sube$`): Set `$A sube B$`  if `$AA x in A", " x in B$`

**Partition**: Set `$P$` is a partition of set `$A$` if:

* `$P_1 uu P_2 uu P_3 ... uu P_("len"(P)) = A$`
* `$O/ !in P$`
* `$AA P_i, P_j in P, P_i !-= P_j -> P_i nn P_j -= O/$`
  * `$P_1 nn P_2 ... nn P_n$` should NOT be used in definition: It doesn't guarantee all sets are mutually exclusive
  * `${1,2} nn {2,3} nn {3,4} -= O/$` will pass this test even when there is overlap of `$3$` between some sets

**Function Formal Definition/Type Annotation**: `$F : D -> CD$` where `$D$` is the domain set and `$CD$` is the co-domain set

* Notation that shows expected inputs and outputs (domains and co-domains/ranges) of a function
* Rule: `$AA d in D, EE cd -= F(A), cd in CD $`: Every domain value must map to at least 1 co-domain value
* Example function `$F : A -> P(A)$`
  * `$A$` is any set of values ,`$P(A)$` is the power set of A

**Onto Function**: A function `$f: A -> B$` is onto if:

* `$AA b in B, EE a in A, f(a) -= b$`

**One to One Function**: A function `$f: A -> B$` is a one to one function if:

* `$AA x,y in A, x !-= y ->  f(x) !-= f(y)$`
* Contrapositive (easier to use sometimes): `$AA x, y in A, f(x) -= f(y) -> x -= y$`

**Asymptotically Smaller Functions**: Function $f(x) \ll g(x)$ if `$lim_(x->oo) (f(x))/(g(x)) = 0 $`

**Asymptotically Similar Functions**: Function `$f(x) ~~ g(x)$` if `$lim_(x->oo) (f(x))/(g(x)) = c$` where `$c in RR$`

**Big O**: Function `$f(n) = O(g(n)) iff EE c,k in RR, c > 0 ^^ k > 0, 0 <= f(n) <= c g(n)$` for every `$n >= k$`

* Functions will have positive outputs as they progress
* `$<= $` type relation, similar to asymptotically smaller but allows for `$<=$` and not just `$<$`
* `$Theta(g)$` is for `$=$` only relation between functions
  * `$f(n)$` is `$Theta(n)$` when `$f(n)$` is `$O(g(n))$`  and `$g(n)$` is `$O(f(n))$`
