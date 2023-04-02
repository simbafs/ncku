# 天文學一期中考

## 宇宙學

### 亂七八糟的宇宙常數

$$
u \propto T^4 \\
H = {\dot a \over a} \\
H^2 \propto \rho(宇宙物質密度) \\
\rho_m \propto a^{-3} \\
\rightarrow H \propto a^{-3/2}\\
\rightarrow a \propto t^{2/3}\\
{a_0 \over a} = 1+z \\
$$

### 溫度與能量

from $E = k_BT$, $1eV \approx 10^4K$

### 一些簡單的反應式

$$
\ce{n + e^+ <=> p + \bar{\nu_e}} \\
\ce{n + \bar{\nu_e} <=> p + e^-} \\
\ce{n <=>[\beta\ decay] p + e^- + \bar{\nu_e}} \\
\ce{n + p <=> D + \gamma}
$$

### 物質組成

$$
{N_n \over N_p} = {1 \over 7} \\
\ce{2n + 14p -> (2n + 2p) + 12p -> He + 12H} \\
{m_{He} \over n_H} = {4 \times 1 \over 1 \times 12} = {1 \over 3}
$$

## 天球座標

|      英文       | 中文 |  單位  |
| :-------------: | :--: | :----: |
| Right Ascension | 經度 |  hour  |
|   Declination   | 緯度 | degree |

## 潮汐力

$$
F_g = \frac{GMm}{L^2}\left[1+\left(\frac{2r}{L}\right)\cos\theta\right] \\
\theta: \text{物體的軸與中心點和大質量星體連線的夾角}
$$

## solid angle

$$
A(\theta_1, \phi_1) \\
B(\theta_2, \phi_2) \\
\overline{AB} = 2 - 2\cos\theta_1\cos\theta_1\cos(\phi_1 - \phi_2) - 2\sin\theta_1\sin\theta_2 \\
\delta\text{($A$, $B$ 夾角)} = \cos^{-1}\left[\cos\theta_1\cos\theta_1\cos(\phi_1 - \phi_2)+\sin\theta_1\sin\theta_2\right] \approx \sqrt{(\Delta\theta)^2+\cos^2\theta(\Delta\phi)^2}
$$

## 角動量

$$
\frac{1}{r_0} = \frac{GMm^2}{L^2}
$$

## The Virial Theorem

in a gravitational bound system

$$
K = -{1 \over 2} U
$$

$$
\text{let }Q := \sum_im_i\vec{v_i}\cdot\vec{r_i} = {1 \over 2}{dI \over dt} \\
{dQ \over dt} = 2K + \sum_i\vec{f_i}\cdot\vec{r_i} = 2K+U
$$

## 星等/Luminosity/color

| name       | symbol | dimension                          |
| :---:      | :---:  | :---:                              |
| Luminosity | L      | $J \cdot s^{-1} = W$               |
| flux       | F      | $W \cdot m^{-2}$                   |
| intensity  | I      | $W \cdot m^{-2} \cdot \Omega^{-1}$ |

$$
F\text{(flux)} = {L \over 4\pi D^2}
$$

### magnitude

$$
m = -2.5\log F+ZeroPoint
$$

### AB magnitude

$$
m_{AB} = -2.5\log{F \over erg \cdot cm^{-2} \cdot s^{-1}} - 48.6
$$

### Vega magnitude

$$
m_{vega} = -2.5\log{F \over F_{vega}}
$$

### Absolute magnitude

$$
M = -2.5\log{F_{10pc}} = -2.5\log F - \underbrace{5\log{D \over 10pc}}_{DM\text{: distance modulus}}
$$

## black body radiation
$$
n = \frac{2L}{\lambda}, N = \frac{4\pi}{3}n^3\frac{1}{8} = \frac{4\pi}{3}\frac{L^3}{\lambda^3}\\
\frac{dN_{\lambda}}{d\lambda} = -\frac{4\pi L^3}{\lambda^4}, \frac{dn_{\lambda}}{d\lambda} = \frac{\overbrace{2}^{polorization}\times4\pi}{\lambda^4}
$$

### Planck Law
$$
\nu = \frac{c}{\lambda} \\
u_\lambda = \frac{8\pi hc}{\lambda^5}\left(\frac{1}{e^{hc \over k_BT\lambda}-1}\right) \\
u_\nu = \frac{8\pi \nu^2}{c^3}\left(\frac{h\nu}{e^{h\nu \over k_BT}-1}\right)
$$

### Wien's Displacement Law
$$
\lambda_{max} \cdot T = 2.89\times10^{-3}
$$


$$
u = \int u_\lambda d\lambda = \frac{8\pi^5K_B^4}{15h^3c^3}T^4 \approx 10^{-15}T^4 \\
flux = uc = 4\pi I\\ 
$$

### Stefan-Boltzmann

$$
f\text{(星體表面的通量)} = \int f\cos\theta d\Omega = I\pi \\
f_B = 10^{-7}T^4(\frac{J}{m^2sK^4}) \\
L_* = \int f_B dA =4\pi R_*^2\sigma T^4\\
F_*\text{(距離 D 的通量)} = \frac{L_*}{4\pi D^2}
$$
