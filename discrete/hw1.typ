#import "template.typ": project
#import "@preview/cetz:0.2.2"
#import "@preview/cetz-venn:0.1.1": venn3, venn2

#show: project.with(
  hw: 1,
)

= 1a
A set with n elements $a_1, a_2, ..., a_n$ has $2^n$ subsets, one of which is the set itself, so it has $2^n-1$ proper subsets. 

$ 2^(|A|)-1 = 127 => |A| = 7 $

= 1b
In all subsets of a set A with n elements, half of them has odd cardinality and half of them has even cardinality. So there are $2^n / 2$ subsets has odd/even cardinality.

$ 2^(|B|) / 2 = 128 => |B| = 8 $

= 2

== (a)

$ B &= {2b + 2 + 1 | b in ZZ} \
&= {2(b+1) + 1 | b in ZZ}\
&=^(forall b in ZZ, b+1 in ZZ) {2b + 1 || b in ZZ} = A $

$ C &= {2c-3 | c in ZZ} \
&= {2c-4+1|c in ZZ} \
&= {2(c-2)+1|c in ZZ} \
&=^(forall c in ZZ, c-2 in ZZ) {2c+1|c in ZZ} = A $
$ A = B and A = C => A = B = C => "(a) is true" $

== (b)

$ E = {3e+2|e in ZZ} = {3e+1+1|e in ZZ} = {3(e + 1/3)+1 | e in ZZ} $
but $e + 1/3$ is not always an integer, so $E != D => "(b) is false"$

== (c)

$ F &= {3(f-1)+1|f in ZZ} \
&= {3f-2|f in ZZ} \
&= {3f-3+1|f in ZZ} \
&= {3(f-1)+1|f in ZZ} \
&=^(forall f in ZZ, f-1 in ZZ) {3f+1|f in ZZ} = D => "(c) is true" $

== (d)

from (b) and (c), we know that $E != D and F = D$, so $E != F => "(d) is false"$

== (e)

Because element in a set is unique, so $G = {emptyset} => "(e) is false"$

= 3

== $ overline(A union B) subset.eq overline(A) sect overline(B) $
$ 
a in overline(A union B) &=> a in.not A union B \
&=> a in.not A and a in.not B \
&=> a in overline(A) and a in overline(B) \
&=> a in overline(A) sect overline(B) \
&=> overline(A union B) subset.eq overline(A) sect overline(B)
$

== $ overline(A) sect overline(B) subset.eq overline(A union B) $

$
a in overline(A) sect overline(B) &=> a in overline(A) and a in overline(B) \
&=> a in.not A and a in.not B \
&=> a in.not A union B \
&=> a in overline(A union B) \
& => overline(A) sect overline(B) subset.eq overline(A union B)
$

from two parts above, we have $ overline(A union B) subset.eq overline(A) sect overline(B) and overline(A) sect overline(B) subset.eq overline(A union B) => overline(A union B) = overline(A) sect overline(B)$

= 4

$
(A - B) union (B -A) \
= (A sect overline(B)) union (B sect overline(A)) "definition of difference" \
= emptyset "definition of complimentary set"
// = (A union B) sect (A union overline(A)) sect (overline(B) union B) sect (overline(B) union overline(A)) "distributive law" \
// = (A union B) sect (overline(B) union overline(A)) "definition of set compliment" \
// = (A union B) sect overline(B sect A) "DeMorgan's Law" \
$

= 5I

By definition of symmetric difference $A Delta B = (A-B) union (B-A)$
#figure(
  caption: [Venn Diagram of $A Delta B$ (gray)],
  cetz.canvas({
    import cetz.draw: *

    venn2(name: "venn", a-fill: gray, b-fill: gray)
    content("venn.a", [A])
    content("venn.b", [B])
  })
)

#figure(
  caption: [Venn Diagram of $A Delta (B sect C)$ (gray)],

  cetz.canvas({
    import cetz.draw: *

    scale(1.5)
    venn3(name: "venn", 
      bc-fill: gray, 
      a-fill: gray,
      ab-fill: gray,
      ac-fill: gray,
    )

    content("venn.a", [A])
    content("venn.b", [B])
    content("venn.c", [C])
  })
) <5I-1>

#figure(
  caption: [Venn Diagram of $A Delta B$ and $A Delta C$],
  grid(columns: (1fr, 1fr), 
    cetz.canvas({
      import cetz.draw: *

      scale(1.5)

      venn3(name: "venn", 
        a-fill: gray,
        ac-fill: gray,
        b-fill: gray,
        bc-fill: gray,
      )

      content("venn.a", [A])
      content("venn.b", [B])
      content("venn.c", [C])
    }),
    cetz.canvas({
      import cetz.draw: *

      scale(1.5)

      venn3(name: "venn", 
        a-fill: gray,
        ab-fill: gray,
        c-fill: gray,
        bc-fill: gray,
      )

      content("venn.a", [A])
      content("venn.b", [B])
      content("venn.c", [C])
    })
  )
)

#figure(
  caption: [Venn Diagram of $(A Delta B) sect (A Delta C)$ (gray)],

  cetz.canvas({
    import cetz.draw: *

    scale(1.5)
    venn3(name: "venn", 
      a-fill: gray,
      bc-fill: gray
    )

    content("venn.a", [A])
    content("venn.b", [B])
    content("venn.c", [C])
  })
) <5I-2>

because @5I-1 and @5I-2 are different, so the statement is false

= 5II

$ emptyset = (overline(A) union overline(B)) sect (overline(A) union B) sect (A union overline(B)) sect (A union B) $

= 6a

$ A subset.eq C => A union C = C, B subset.eq C => B union C = C $
$ => |A union B union C| = |C| = 1000 $

= 6b

$ A sect C = A sect B = B sect C = emptyset => A sect B sect C = emptyset $
$ => |A union B union C| = |A| + |B| + |C| = 1110 $

= 6c

$ (A sect C) subset.eq B => |A sect B sect C| = |A sect C| = 2 $
$
|A union B union C| &= |A| + |B| + |C| - |A sect B| - |A sect C| - |B sect C| + |A sect B sect C| \
&= 1110 - 4 - 4 - 2 + 2 = 1102 
$

= 6d

$
100 = |A union B| = |A| + |B| - |A sect B| = 10 + 100 - |A sect B| \
=> |A sect B| = 10 \
$

$
|A sect B| = 10 => A subset.eq B => A = A sect B \
=> |A sect B sect C| = |A sect C| = 3 
$

$
|A union B union C| &= |A| + |B| + |C| - |A sect B| - |A sect C| - |B sect C| + |A sect B sect C| \
&= 1110 - 10 - 3 - 20 + 3 = 1080 
$

= 7

#figure(
  caption: [Students who have learned C, Python, Java],

  cetz.canvas({
    import cetz.draw: *

    scale(1.5)
    venn3(name: "venn", 
    )

    content("venn.a", [C(a)])
    content("venn.b", [Python(b)])
    content("venn.c", [Java(c)])
    content("venn.ab", [(ab)])
    content("venn.ac", [(ac)])
    content("venn.bc", [(bc)])
    content("venn.abc", [(3)])
  })
) 
#let ab = math.op("ab")
#let ac = math.op("ac")
#let bc = math.op("bc")
#let abc = math.op("abc")

- "class has a total of 42 students" $ => a+b+c+ab+ac+bc+abc= 42 $ <all>
- "students that have learned all three programming languages" $ => abc = 3 $ <abc>
- "students who have learned C", $ => a+ab+ac+abc=30 => a+ab+ac=27 $ <a>
- "students who have learned Python", $ => b+ab+bc+abc = 25 => b+ab+bc=23 $ <b>
- "students who have learned Java", $ => c+ac+bc+abc=12 => c+ac+bc=9 $ <c>


== 7a

Adding up @a, @b, @c, @abc and subtract @all, we get $ ab+ac+bc=19 $<two-language>. So there are *19* students have learned exactly two programming languages.

== 7b

@all subtract @abc and @two-language, we get $ a+b+c = 20 $, So there are *20* students have learned exactly one programming language.

= 8

The problem equivalent to find the probability that thw sum of two randomly selected numbers from 1 to 100 are even. To get an even sum, it can be odd+odd or even+even. So there are $ binom(50, 2) + binom(50, 2) $ possible combinations. And the final probability is $ (binom(50, 2) + binom(50, 2))/binom(100, 2) = (cancel(2 * 50) * 49 \/ cancel(2, inverted: #true)) / (cancel(100)*99\/cancel(2, inverted: #true)) = 49/99 $

= 9a

$ A times B = {{a, x}, {a, y}, {b, x}, {b, y}} $

= 9b

$ B times A = {{x, a}, {x, b}, {y, a}, {y, b}} $

= 9c

If $x=a, y=b$ or $x=b, y=a$, then $A times B = B times A$

= 10a

$ Pr(A) = (|{3, 6, 9, 12, 15}|)/15 = 1/3 $

= 10b

$ Pr(B) = (|{11, 12, 13, 14, 15, 16, 17}|)/15 = 2/5 $

= 10c

$ Pr(A sect B) = (|{12, 15}|)/15 = 2/15 $

= 10d

$ Pr(A union B) = (|{3, 6, 9, 11, 12, 13, 14, 15, 16, 17}|)/15 = 2/3 $

= 10e

$  Pr(C union D) = Pr(C) + Pr(D) - Pr(C sect D) = 0.3 + 0.4 - 0.2 = 0.5 $

