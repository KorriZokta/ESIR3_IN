function M = transfo_rigide(theta, omega, phi, p, q , r)

Rx = [    1            0             0        0 ;
          0       cos(theta)   -sin(theta)   0 ; 
          0       sin(theta)    cos(theta)   0 ;
          0            0             0        1 
     ];
 
Ry = [cos(omega)       0        -sin(omega)   0 ;
          0            1             0        0 ; 
      sin(omega)       0         cos(omega)   0 ;
          0            0             0        1 
     ];
 
Rz = % A COMPLETER %

T  = % A COMPLETER %
 
M = T*Rz*Ry*Rx;