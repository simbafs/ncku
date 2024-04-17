#import "@preview/touying:0.4.2": *
// Register university theme
// You can replace it with other themes and it can still work normally
#let s = themes.university.register(aspect-ratio: "16-9")

// Set the numbering of section and subsection
#let s = (s.methods.numbering)(self: s, section: "1.", "1.1")

#let s = (s.methods.colors)(
  self: s,
  primary: rgb("#5C2FC2"),
  secondary: rgb("#5C88C4"),
  tertiary: rgb("#6FDCE3"),
)


// #set text(font: "DFKai-SB", lang: "zho", size: 14pt)
// #set text(font: "PingFang TC", lang: "zho")
#set text(font: "jf open 粉圓 1.1", lang: "zho")
#show math.equation: set text(54pt)

// Set the speaker notes configuration
// #let s = (s.methods.show-notes-on-second-screen)(self: s, right)

#let acenter = (body) => align(center + horizon)[#body]

// Global information configuration
#let s = (s.methods.info)(
  self: s,
  title: [探索星系團的性質：研究 eROSITA 最終赤道深度調查],
  short-title: [探索星系團的性質],
  subtitle: [Exploring Galaxy Cluster Properties: Insights from the eROSITA Final Equatorial Depth Survey],
  author: [C24106082 陳宏彰  指導教授：邱奕儂],
  date: [2024/06/12],
)

// Extract methods
#let (
  init, 
  slides, 
  touying-outline, 
  alert, 
  speaker-note,
  uncover,
) = utils.methods(s)
#show: init

// Extract slide functions
#let (
  slide,
  empty-slide, 
  title-slide, 
  focus-slide,
  matrix-slide,
) = utils.slides(s)
#show: slides

#focus-slide()[
    星系團怎麼形成的？
]

// outline
#touying-outline()


= 如何研究？
== NFW 模型

 === Navarro-Frenk-White（NFW） 模型
#acenter[
  $ rho(r) = rho_0 / (r/R_s (1 + r/R_s)^2) $
]

#acenter(image("../img/nfw-3d.png"))

// by magic

== 二維投影 
#slide()[
  #image("../img/projected.png")
]

#acenter[
  $ "NFW"(r) = 2 rho_0 R_s times f( r/R_s ) $
  #text(20pt)[Keiichi Umetsu. Cluster–galaxy weak lensing. The Astronomy and Astrophysics Review 2020, 28]

  #math.equation()[

  $ f(x) = cases(
    1/(1-x^2)(-1 + 2/sqrt(1-x^2) op("arctanh")(sqrt((1-x)/(1+x)))) &(x<1),
    1\/3 &(x = 1),
    1/(x^2-1)(1-2/sqrt(x^2-1) arctan(sqrt((x-1)/(x+1)))) &(x> 1)

  ) $
  ]
]

#acenter[
  #image("../img/model.png")
]

== 變換參數
#slide()[
  === 密集程度 concentration
  #acenter[
     $ c =  R_"vir" / R_s $ 
     #pause
     $ R_"vir" = R_"500c"$ 
  ]
]

#slide()[
  === 星系數量
  #acenter[
    $ N prop M = integral_0^R_"vir" 4 pi r^2 rho(r) d r \
    = 4 pi rho_0 R_s^4 (ln(1 + c) - c/(1 + c)) $
  ]
]


== 計算密度分佈
#acenter[
  #image("../img/step3.png")
]

== MCMC
Markov chain Monte Carlo 馬可夫鏈蒙地卡羅
#acenter[
  #link("https://chi-feng.github.io/mcmc-demo/app.html?algorithm=RandomWalkMH&target=banana")[single walker(link)]

  #link("https://chi-feng.github.io/mcmc-demo/app.html?algorithm=SVGD&target=banana&delay=0")[multiple walkers(link)]
]

== 擬合
#grid(
  columns: (1fr, 1fr),
  align: bottom,

  image("../img/nfw.png"),
  image("../img/corner.png")
)

== 背景星系
#acenter[
  #image("../img/background-schematic.png")
]

= 更進一步

== 根據星系紅移篩選
#focus-slide()[星系距離我們多遠？]

#acenter[
  紅移 $=>$ 遠離速度 $=>^#text(34pt, font: "jf open 粉圓 1.1")[哈伯定律]$ 距離 #text(60pt, fill: red)[？]
]

#acenter[
  #image("../img/redshift.png")
]

#acenter[
  #image("../img/redshift-cumsum.png")
]

#acenter[
  #image("../img/step1.png")
]


== 根據星系星等篩選
#grid(
  columns: (1fr, 2fr),
  align: horizon,
  
  [
    + 上限：太暗的星系看不到
    + 下限：超過「星系團中最亮的的星系」的肯定不是
  ],
  image("../img/m_.png")
)

#acenter(image("../img/step2.png"))

#grid(
  columns: (1fr, 1fr),
  align: center,

  image("../img/sample-model.png"),
  image("../img/nfw.png"),
  [篩選前], [篩選後]
)

#grid(
  columns: (1fr, 1fr),
  align: center,

  image("../img/sample-corner.png", height: 80%),
  image("../img/corner.png", height: 80%),
  [篩選前], [篩選後]
)
= 結果

#acenter(image("../img/result.png"))

#focus-slide[謝謝大家]
