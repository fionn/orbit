ORBIT
=====
This code numerically solves the _n_-body problem using the leapfrog algorithm, a time-reversible [symplectic integrator](https://en.wikipedia.org/wiki/Symplectic_integrator).

Build
-----
Clone and `make`.

Run
---
`./orbit file`, where `file` contains the number of "planets", their masses and their initial positions and velocities.

    Number of planets
    Mass of planet
    x    y    v_x    v_y

See `examples/test2.dat` and `examples/test3.dat` for examples (with stable orbits for _n_ = 2, _n_ = 3 respectively). It prints all output to `stdout` in the format

    x_0    y_0    x_1    y_1    ...    x_n    y_n
    
for each timestep, where (_x_<sub>_i_</sub>, _y_<sub>_i_</sub>) is the coordinate of the _i_<sup>th</sup> planet in the inertial reference frame of the 0<sup>th</sup> planet (under a coordinate transformation sending the 0<sup>th</sup> planet to the origin).

The energy and angular momentum of the system are also calculated with `energy()`, `angularmomentum()` (commented in `main()`, ll 153, 154).

![3-body](graph/ring_cairo.png)

