# A math page to test latex


When given a first order differential equation $dy/dx = M(x,y)$
if it is Separable then:
	$dy/dx = P(x)/Q(x)$
If it's Linear then:
	$dy/dx + p(x)y = q(x)$
		Good luck

Falling under Air Resistance:
For high velocitues, the ari resistence is better modelled as being proportional to the square of the speed
$m\frac{dv}{dt} = mg-1/2(D\rho*Av^2)$
$D$ - drag coefficient (which is dimensionless)
$\rho$ - air density
$A$ - cross-sectional area of the object

left side is mass * acceleration or derivative of velocity

is there a terminal velocity?
let $v(t)=v_\infty$  be constant, and substitute into the ODE
$v_\infty = \sqrt{\frac{2mg}{D\rho A}}$
is this a sensible terminal velocity cause for all values they must tend to this terminal velocity whether its above or below it
to show that this happens we can step through the problem

$\begin{align}
m\frac{dv}{dt} = mg-\frac{1}{2}D\rho Av^2\\
\frac{dv}{dt} = g- \frac{1}{2m}D\rho Av^2\\
= \frac{D\rho A}{2m}(v^2_\infty - v^2)\\
= -k(v^2-v^2_\infty).
\end{align}$

The ODE is seperable
$\begin{align}
\frac{dv}{dt} = -k(v^2-v^2_\infty)\\
\frac{dv}{v^2-v^2_\infty} = -kdt
\end{align}$

$\begin{align}
\int{\frac{dv}{v^2-v^2_\infty}} = -k\int dt\\
\frac{1}{v^2-v^2_\infty} = \frac{1}{2v_\infty}\frac{dv}{v-v_\infty}-\frac{1}{2v_\infty}\frac{dv}{v+v_\infty}\\
\end{align}$
