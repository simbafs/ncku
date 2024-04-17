// Get Polylux from the official package repository
#import "@preview/polylux:0.3.1": *
#import themes.simple: *

// Make the paper dimensions fit for a presentation and the text larger
#set page(paper: "presentation-16-9")
#set text(font: "DFKai-SB", lang: "zho", size: 24pt)

// Use #polylux-slide to create a slide and style it using your favourite Typst functions
#polylux-slide[
  #align(horizon + center)[
    #text(size: 40pt, weight: "bold")[ 探索星系團的性質：\
    研究 eROSITA 最終赤道深度調查 ]

    #text(size: 20pt)[ Exploring Galaxy Cluster Properties: Insights from the eROSITA Final Equatorial Depth Survey]

    陳宏彰 C24106082 / 指導教授：邱奕儂

    2024/06/12
  ]
]

#focus-slide[
  暗物質是什麼？

  #pause

  星系團是怎麼形成的？
]

#slide[
  // outline
  = Outline
  #utils.polylux-outline()
]

#utils.register-section("研究步驟")
#centered-slide[
  = 研究步驟
]


#title-slide[
  = Keep it simple!
  #v(2em)

  Alpha #footnote[Uni Augsburg] #h(1em)
  Bravo #footnote[Uni Bayreuth] #h(1em)
  Charlie #footnote[Uni Chemnitz] #h(1em)

  July 23
]

#slide[
  == First slide

  #lorem(20)
]

#focus-slide[
  _Focus!_

  This is very important.
]

#centered-slide[
  = Let's start a new section!
]

#slide[
  == Dynamic slide
  Did you know that...

  #pause
  ...you can see the current section at the top of the slide?
]
