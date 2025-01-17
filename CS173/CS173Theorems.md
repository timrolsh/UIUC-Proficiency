# CS 173 Theorems

**Division Algorithm**: $\displaystyle\forall{A},{B}\in\mathbb{Z},\exists!{Q},{R}\in\mathbb{Z},{A}={B}{Q}+{R}$

* B is positive, Q and R are quotient and remainder respectively
* Remainder must be non negative (cpp does negative remainders so make sure to mod add until its positive, was issue in quadmod in john)

**Quotient/Remainder/GCD**: If you have $\frac{A}{B}$, $\text{gcd"(A,B) = "gcd} \left(B , R\right)$

* R is remainder for $\frac{A}{B}$ by division algorithm
