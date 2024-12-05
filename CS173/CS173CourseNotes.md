# CS 173 Notes
## Chapters to Learn
4
5
7
8
9
10
11
12
13
14
15.1-15.9
16
17
18
19
20
come back to 6 if it is productive

## Exam Info
The student code does not allow you to take the CS 173 Proficiency Exam after taking CS 374 (or a more advanced theoretical CS course).

The website for the Fall 2023 offering of CS 173 has a current set of skills lists, lecture notes, and videos. Course websites for Spring 2019 and earlier have old hardcopy exams that you can use for practice. (We have since moved the exams online.)

The exam will include some free-response questions (e.g. proofs) which are manually graded, so it will take a few days for results to be available. Details will be posted here in August about how to enroll for the exam on Prairielearn and how to access a “Sandbox”
assessment with notes on how to format your free-response work (LaTeX is not required).

3 hours CBTF

USE THIS SITE TO STUDY: https://courses.grainger.illinois.edu/cs173/fa2024/ALL-lectures/lectures.html

use this site for other exams: https://courses.grainger.illinois.edu/cs173/sp2019/A-lecture/Exams/index.html

## Math Review
`$ZZ", " ZZ^+", "ZZ^-$`: The set of all integers, positive, negative integers, respectively
* Zero is in neither positive or negative sets
`$RR$`: The set of all real numbers
* `$RR^2$`: The real plane in 2D
* `$EE (x,y) in RR^2", " x^2 + y^2 = 1$`: Definiton for unit circle
`$QQ$`: The set of all rational numbers
`$CC$`: The set of all complex numbers
`$n choose k = n!/(k!(n-k)!)$`
Floor: The largest integer$\displaystyle{\left\lfloor{{3.75}}\right\rfloor}={3}$, $\displaystyle{\left\lfloor{-{3.75}}\right\rfloor}=-{4}$
Finite geometric series formula: `$sum_(k=0)^n r^k = (r^(n+1) -1)/(r-1)$`
* Closed form, expression for geometric series that isn't `$r=1$`
Important closed form of summation: `$sum_(i=1)^n i = (n(n+1))/2$`
`$epsilon$`: empty string
Alphabet (A): The set of all characters that can be used to make strings
* `$A^"*"$`: The set of all finite length strings that can be made from a character
**Regular Expressions**: Notation used to specify patterns for similar sets of strings
* `$a|b$`: either character a or b
* `$a^"*"$`: zero or more copies of character a
## Logic
`$^^$`: and
`$vv$`: or
`$not$`: not
`$o+$`: xor, not equal, exclusive or, or but they cannot both be true, only one can be true
`$p -= q$`: Logically equivalent
**Logic Precedence**: `$not", " ^^ ", " vv ", etc."$`
**Propositional Logic**: Logic based on propositions, which require a statement to be true or false, but not both
* No variables in propositional logic, statements must be explicit claims
* `$x < 9$`: invalid in propositional logic
**Predicate Logic**: Propositional logic but includes variables
### Conditionals Review
`$p -> q = not p vv q$`: conditional, if p then q
* Notation: p is hypothesis, q is conclusion
`$q -> p$`: converse, not equivalent statements
`$p harr q$`: biconditional, `$(p -> q) ^^ (q -> p) $`
* If and only if concept
`$not q -> not p$`: contrapositive, `$not q -> not p = p -> q$`
**Demorgan's Laws**
* `$not (p vv q) -= not p ^^ not q$`
* `$not (p ^^ q) -= not p vv not q$`
**Distributive Property in Logic**
* `$p ^^ (q vv r) -= (p ^^ q) vv (p ^^r)$`
* `$p vv (q ^^ r) -= (p vv q) ^^ (p vv r)$`
**Quantifiers**: Tell you about how many entries in a set meet or should meet a condition
* `$AA$`: for all
* `$EE$`: There exists
		`$AA$` and `$EE$` usually negate each other, an existential statement can be used to disprove a universal statement and vise versa
* `$EE!$`: There exists unique, only one
* `$in $`: is in
* Transforming quantifier statements: `$AA x", " y -> z$`
	* Contrapositive: `$AA x", " not z -> not y$`
	* quantifier stays the same
* Negation: `$notAA x", " p -= EE x", " not p$`, `$not EE x", " p -= AA x", " not p$`
## Proofs
proof by contrapositive, proof by induction, proof by contradiction
### Direct Proofs
* For proving `$AA x in A ", " P(x) $`, pick representative value for `$x$`
* Definitions defined with if are designed to work both ways
* A number `$q$` is rational if it can be written as `$q = m/n", " m", " n in ZZ$`
* This definition and the if in this context can be read both ways
* Try and put claim into conditional form, this is the easiest to prove
* Even definition: `$n in ZZ$` is even if `$EE m in ZZ", " n = 2m$`
* Odd definition: `$n in ZZ$` is odd if `$EE m in ZZ", " n = 2m + 1$`
**Outline**:
* Start from variable declarations and hypothesis
* Move to information that needs to be proved
**Proof of Cases**: When you're proving a logical statement that involves `$vv$`, do a subproof for each statement separated by the `$vv$`
**Example #1**:
* Claim: If `$q$` is rational, `$2q$` will also be rational
* Proof: Let `$q$` be a rational number. We know that `$q = m/n$` where `$m", " n in ZZ$` by the definition of a rational number. `$2m$` is an integer as 2 is an integer, and multiplying 2 integers gives you an integer. `$2q = (2m)/n$`, and since both the numerator and denominator are integers, `$2q$` will be a rational number as it is the ratio of two integers.
**Example #2**: Claim: `$AA x in ZZ$` where `$x$` is odd, `$x^2$` will also be odd
Proof: 
`$x in ZZ$` is odd if  `$EE m in ZZ", " x = 2m + 1$` by the definition of an odd number. 
`$x = 2m + 1", " x^2 = (2m+1)^2 = 4m^2 + 4m + 1 = 2(2m^2 + 2m) + 1$`.
We know that `$2m^2 + 2m$` will be an integer because m is an integer and integer operations are being performed on it. Therefore, `$EE o in ZZ", " o = 2m^2 + 2m$`. Therefore, `$x^2 = 2o + 1$`, and `$x^2$` is an odd integer.
### Examples/Counter Examples
Prove `$AA$` (universal statement): General proof
Prove `$not AA$`: Use `$EE$` counter example
Prove `$EE$` (existential statement): Give an example
Prove `$not EE$`: Use a `$AA$` proof
**Example 3**: Claim: `$EE x in ZZ", " x^2 = 0$`
Proof:
`$0$` is such a number. `$0^2 = 0$`. So the statement is true.
* You can use concrete example for existential proofs, don't have to do general value
**Example 4**: Claim: Every rational number `$q$` has a multiplicative inverse. 
Proof: Take an example of a rational number `$q = 0/1$` made up of a ratio of two integers. The multiplicative inverse of `$q$`, `$r$` is a value such that `$qr=1$`. Because `$q = 0/1 = 0", " 0 xx A = 0 AA A in RR$`, `$q$` is a counter example of at least one rational number that does have a multiplicative inverse. This claim is therefore false. 
### Proof By Contrapositive
* Quantifier `$p -> q$` goes to Quantifier `$not q -> not p$`
* Different from negating quantifiers, quantifier stays the same because the expression remains logically equivalent
## Number Theory
**Number Theory**: Branch of mathematics focused on behavior of integers
* Applications to cryptography, algorithms for randomization
* Common questions are which integers divide evenly, which integers are prime, etc.
**Factor Notation**: A divides B or A is a factor of B is written as `$A | B$`
Tip: Avoid using `$B/A$` and putting factors into ratios unless you have to, just use multiplication instead to avoid making the problem more complex
**Notation for greatest common divisor**: `$"gcd"(a,b)$`
**Relatively Prime**: Two numbers that share no common factors, `$"gcd"(a,b)=1$`
**Euclid's GCD Algorithm**
* First you take the theorem that `$"gcd"(a,b) = "gcd"(b,r)$` for division algorithm
* Recursively apply this problem (your `$b", " r$` output becomes the next `$a", " b$` input so you can get the next `$b", " r$` pair) until you hit your base case of `$r = 0$`
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
CONTINUE FROM 4.10