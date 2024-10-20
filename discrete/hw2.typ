#import "template.typ": project
#import "@preview/truthfy:0.4.0": truth-table, truth-table-empty

#show: project.with(
  hw: [Discrete Math Homework 2],
)

#let False = math.op("False")
#let True = math.op("True")

= 1

$
(p or q) and (p or not q) \
= p or (q and not q) \
= p or False \
= p
$

= 2

1. $p->r$ with law of syllogism of a and b
2. $not p$ with Modus Tollens of 1. and c.

= 3

$
(p and not p) -> (q or not q)\
= False -> True\
= True
$

this is a tautology

= 4

== (a)

#table(
  columns: (auto, )*6,
  $p$, $q$, $not q$, $p or not q$, $not(p or not q)$, $not(p or not q) -> p$,

  [0], [0], [1], [1], [0], [1],
  [0], [1], [0], [0], [1], [0],
  [1], [0], [1], [1], [0], [1],
  [1], [1], [0], [1], [0], [1]
)

== (b)

#table(
  columns: (auto, )*8,
  $p$, $q$, $not p$, $not q$, $not p or not q$,  $q -> (not p or not q)$, $(not p or not q) -> q$, $q <-> (not p or not q)$,

  [0], [0], [1], [1], [1], [1], [0], [0],
  [0], [1], [1], [0], [1], [1], [1], [1],
  [1], [0], [0], [1], [1], [1], [0], [0],
  [1], [1], [0], [0], [0], [0], [1], [0] 
)

// #truth-table($q => (not p or not q)$, $(not p or not q) => q$, $q <=> (not p or not q)$)

== (c)

#table(
  columns: (auto, )*5,

  $p$, $q$, $p->q$, $q->p$, $(p->q)->(q->p)$,

  [0], [0], [1], [1], [1],
  [0], [1], [1], [0], [0],
  [1], [0], [0], [1], [1],
  [1], [1], [1], [1], [1]
)

// #truth-table($p => q$, $q => p$, $(p => q) => (q => p)$)

== (d)

#table(
  columns: (auto, )*5,

  $p$, $q$, $r$, $q->r$, $p->(q->r)$,

  [0], [0], [0], [1], [1],
  [0], [0], [1], [1], [1],
  [0], [1], [0], [0], [1],
  [0], [1], [1], [1], [1],
  [1], [0], [0], [1], [1],
  [1], [0], [1], [1], [1],
  [1], [1], [0], [0], [0],
  [1], [1], [1], [1], [1],
)

== (e)

#table(
  columns: (auto, )*8,

  $p$, $q$, $r$, $p->q$, $q->r$, $(p->q) and (q -> r)$, $p -> r$, $[(p->q) and (q -> r)] -> (p -> r)$,

  [0], [0], [0], [1], [1], [1], [1], [1],
  [0], [0], [1], [1], [1], [1], [1], [1],
  [0], [1], [0], [1], [0], [0], [1], [1],
  [0], [1], [1], [1], [1], [1], [1], [1],
  [1], [0], [0], [0], [1], [0], [0], [1],
  [1], [0], [1], [0], [1], [0], [1], [1],
  [1], [1], [0], [1], [0], [0], [0], [1],
  [1], [1], [1], [1], [1], [1], [1], [1],
)

= 5

== (a)

$
[not q and (not r or q or not q)] or [(r or t or not r) and p] \
= [not q and (not r or True)] or [(t or True) and p] \
= (not p and not r) or (p and t) \
$

== (b)

$
[p or (p and t) or (p and q and not r)] and [(p and r and t) or t]\
= [p and (t or (q and not r))] and [p and r and t]\
= (t or (q and not r)) and p and r and t 
$

= 6

#table(
  columns: (auto, auto),
  [a], [today is a holiday],
  [b], [Alice will go out to have fun],
  [c], [Alice pass the exam],
)

the argument is
$
a -> b \
b -> not c
$
, which concludes that $a -> not c$. The desired conclustion $not a -> c$ is a inverse of our concludes. So it is invalid.

= 7

Proof of "Law of the Syllogism"

$$

$ 
&underbrace((p -> q)) and underbrace((q -> r)) -> underbrace((p -> r)) &"with " p -> q <=> not p or q \
=>& underbrace([(not p or q) and (not q or r)] -> (not p or r)) &"with " p -> q <=> not p or q \
=>& underbrace(not [(not p or q) and (not q or r)]) or (not p or r) &"with DeMorgan's Law"\
=>& underbrace(not (not p or q)) or underbrace(not (not q or r)) or (not p or r) &"with DeMorgan's Law"\
=>& (p and not q) or (q and not r) or not p or r &"re-arrange"\
=>& underbrace((p and not q) or not p) or underbrace((q and not r) or r) &"distributive property"\
=>& [underbrace((p or not p)) and (not q or not p)] or [(q or r) and underbrace((not r or r))] &"inverse law"\
=>& underbrace([True and (not q or not p)]) or underbrace([(q or r) and True]) &"identity law"\
=>& (not q or not p) or (q or r) &"re-arrange"\
=>& underbrace(not q or q) or not p or r &"inverse law"\
=>& True or not p or r &"domination law"\
=>& True
$

QED

= 8

Assume $p$

1. $p -> (q or r)$, premise
2. $q or r$, step 1. and $p$
3. $r$, step 2. and $not q$
4. $not(r or p)$, permise
5. $not p$, step 4. and 3.
6. $p$, permise
7. $p and not p <=> False$, step 5, and 6. with law of conjunction
8. $not p$, proof by contradiction

= 9

== (a)

$forall x exists y E(x, y)$

== (b)

$forall y exists x not E(x, y)$

== (c)

$(exists x forall y E(x, y)) and (exists y forall x not E(x, y))$

= 10

$p(x) = (x+4)(x-2) = 0 => x = -4, 2$

== (a)

Choose $x = 6$, $q(6)$ is true and $p(6)$ is false. So $q(6) -> p(6)$ is false. So $forall x [q(x) -> p(q)]$ is false.

== (b)

Choose $x = 2$, $q(2)$ is true and $p(2)$ is true. So $q(2) -> p(2)$ is true. So $exists x [q(x) -> p(x)]$ is true.

== (c)

Choose $x = 2$, $p(2)$ is true and $r(2)$ is true. So $p(2) and r(2)$ is true. So $exists x[p(x) and r(x)]$ is true.

== (d)

Consider
- for all odd number $x$, $not q(x)$ is true and $not p(x)$ is true. So $not q(x) -> not p(x)$ is true. 

- for all even number $x$ except 2 and -4, $not q(x)$ is false and $not p(x)$ is true. So $not q(x) -> not p(x)$ is true.

- for $x = 2$ and $x = -4$, $not q(x)$ is false and $not p(x)$ is false. So $q(x) -> p(x)$ is true.

Combine all above, $forall x [not q(x) -> not p(x)] and exists x [q(x) -> p(x)]$ is true.

== (e)

Choose $x = -4$, $p(-4) or q(-4)$ is true, but $r(-4)$ is false. So $forall x[(p(x) or q(x)) -> r(x)]$ is false.
