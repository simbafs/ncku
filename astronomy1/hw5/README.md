# Problem 1

Consider a ball with a radius R, mass M, and a uniform density $\rho = \frac{M}{\frac{4\pi}{3}R^3}$. Please calculate it's self gravitational potential.

$$
\begin{align*}
dU =& \frac{GMdm}{r} = \frac{G(\frac{4}{3}\pi r^3\rho)(4\pi r^2dr \rho)}{r} \\
U =& \int dU = \int^R_0 \frac{16}{3}\pi^2G\rho^2r^4dr = \frac{16}{15}\pi^2G\rho^2R^5 \\
=& \frac{16}{15}\pi^2G\left(\frac{M}{\frac{4}{3}\pi R^2}\right)^2R^5 = \frac{3}{5}GM^2
\end{align*}
$$

# Problem 2

Demonstrate that the derived form of the Kepler's 1st law, $r = \frac{r_0}{1+e\cos\phi}$, where $e$ is ellipticity, $\phi$ is the angle in the polar coordinate, and $r_0$ is a characteristic radius, is a ellipse that can be describedas $\frac{x^2}{a^2}+\frac{y^2}{b^2} = 1$.

$$
\begin{align*}
r^2 =& \left(\frac{r_0}{1+e\cos\phi}\right)^2 \\
x^2+y^2 =& \frac{r_0^2}{1+2e\cos\phi+e^2\cos^2\phi} = \frac{r_0^2}{1+2e\frac{x}{r}+e^2\frac{x^2}{x^2+y^2}} \\
r_0^2 =& x^2+y^2+2exr+e^2x^2 \\
\frac{r_0^2}{1+e^2}+\sqrt{\frac{er}{1+e^2}}^2 =& x^2+2\frac{er}{1+e^2}x+\sqrt{\frac{er}{1+e^2}}^2+\frac{y^2}{1+e^2} \\
=& \left(x+\sqrt{\frac{er}{1+e^2}}\right)^2+\frac{y^2}{1+e^2} \\
\Rightarrow& \frac{x^2}{a^2}+\frac{y^2}{b^2} = 1
\end{align*}
$$

# Problem 3

Given the equation in Problem 2, what is the averaged distance between the star and the orbiting planet? That's, derive $<r> = \frac{1}{2\pi}\int^{2\pi}_{\phi=0}r(\phi)d\phi$

$$
\begin{align*}
<r> =& \frac{1}{2\pi}\int^{2\pi}_{\phi=0}r(\phi)d\phi \\
=&\frac{1}{2\pi}r_0\int^{2\pi}_{\phi=0}\frac{d\phi}{1+e\cos\phi} \\
=&\frac{1}{2\pi}r_0\frac{2\pi}{\sqrt{1-e^2}} \\
=&\frac{r_0}{\sqrt{1-e^2}}
\end{align*}
$$
