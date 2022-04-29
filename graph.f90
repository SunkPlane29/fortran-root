program main
  implicit none

  !declare external function (later it is also declared as a real variable,
  !maybe bacause it's result is a real number?)
  external f3

  real*8 x, xmin, xmax, delx, f3
  integer nx, i

  !assign values to variables like, xmin (the starting point of the graph)
  !xmax (the final point of the graph), nx (number of points in the graph)
  !delx (the rate of change between points in the graph)

  xmin = 0.0
  xmax = 50.0
  nx = 5000
  delx = (xmax - xmin)/dfloat(nx - 1)

  !.dat is a data file
  open (unit=1, file='graph.dat')

  do i = 0, nx-1
     x = xmin + dfloat(i) * delx

     write(1,*) x, f3(x)
  end do

  close(1)

end program main

real*8 function f3(x)
  implicit none

  real*8 x
  f3 = sqrt(x)

  return

end function
