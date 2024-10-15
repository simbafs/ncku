#import "template.typ": project

#show: project.with(
  hw: [數位系統導論 作業一],
)

= Question 1.3

== (c)

$ (435)_8 = 4*8^2 + 3*8^1 + 5*8^0 = 256 + 24 + 5 = 285 $

== (d)

$ (345)_6 = 3*6^2 + 4*6^1 + 5*6^0 = 108 + 24 + 5 = 137 $

= Question 1.16

== (a)
16's complement of C3DF is $16^4$ - C3DF = $(10000)_(16) - ("C3DF")_(16)$ = $(10000 - "C3DF")_(16) = ("3C21")_(16)$

== (b)
$ ("C3DF")_("hex") = (1100 0011 1101 1111)_("bin") $

== (c)
2's complement of 1100 0011 1101 1111 is 1 0000 0000 0000 0000 - 1100 0011 1101 1111 = 0011 1100 0010 0001

== (d)
$ (0011 1100 0010 0001)_("bin") = ("3C21")_("hex") $

= Question 1.23

791 in BCD is 0111 1001 0001 and 658 in BCD is 0110 0101 1000. To sum them, first add them, resulting in 1101 1110 1001. The second digit is larger then 1010, so add 0110 to it. resulting in 1110 0100 1001. Now the third digit is $>=$ 1010, so add 0110 to it, resulting in 0001 0100 0100 1001, which is 1449 in decimal. 

