#import "@preview/physica:0.9.3": *
#import "@preview/colorful-boxes:1.3.1": *

// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!
#let project(
  title: "",
  abstract: [],
  authors: (),
  body,
) = {
  set text(lang: "zho")
  // Set the document's basic properties.
  set document(author: authors.map(a => a.name), title: title)
  set page(
    margin: (left: 25mm, right: 25mm, top: 25mm, bottom: 25mm),
    numbering: "1",
    number-align: center,
  )
  // set text(font: "Linux Biolinum", lang: "zho", size: 14pt)
  set text(font: "DFKai-SB", lang: "zho", size: 14pt)
  // 標楷體在預覽會爛掉，所以輸出時再改成標楷體

  v(50%)

  v(1.2em, weak: true)

  align(center)[
    #text(30pt, "物理實驗報告")

    #text(
      size: 40pt, 
      weight: 700, 
      title
    )

    C24106082 陳宏彰
  ]

  pagebreak()

  // Table of contents.
  set heading(numbering: "1.")
  outline(depth: 4,  indent: true, title: "目錄")
  pagebreak()


  // Main body.
  set math.equation(numbering: "(1)")
  set par(
    justify: false,
    // first-line-indent: 1em,
  )
  set text(hyphenate: false)

  // bibliography
  show bibliography: set heading(numbering: "1.")

  // my settings

  show figure.where(
    kind: table
  ): set figure.caption(position: top)

  // show figure.where(
  //   kind: table
  // ): set figure(
  //   supplement: "表", 
  //   numbering: "一",
  // )
  //
  // show figure.where(
  //   kind: image
  // ): set figure(
  //   supplement: "圖", 
  //   numbering: "一",
  // )

  set image(width: 80%)
  
  // custom heading
  show heading: it => [
    #set text(20pt, weight: "bold")
    #text(counter(heading).display("1.1") + it.body)
    // the following new line is essential

  ]

  set underline(offset: 4pt)

  body
}

#let hbar = text(font: "Linux Libertine", style: "italic")[\u{0127}]
#let hr = line(length: 100%)
#let answer(txt) = underline(text(txt, fill: blue, ), stroke: black)

#let cm = math.op("cm")
#let mm = math.op("mm")
#let nm = math.op("nm")

#let W = math.op("W")
#let mW = math.op("mW")
#let muW = math.op($mu"W"$)

#let mV = math.op("mV")
#let muV = math.op($mu"V"$)

#let mA = math.op("mA")
#let muA = math.op($mu"A"$)
