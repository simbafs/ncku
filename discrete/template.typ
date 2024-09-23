#let project(
  hw: 1,
  body,
) = {
  set math.equation(numbering: "(1)")

  // set page to be A4
  set page(
    "a4",
    margin:2cm,
    header: [Discrete Math HW 1 #h(1fr) C24106082 陳宏彰 #line(length: 100%) ],
    numbering: "1",
  )

  body
}
