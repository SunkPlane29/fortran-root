program main
  implicit none

  !declare external function (later it is also declared as a real variable,
  !maybe bacause it's result is a real number?)
  external f1, f2

  real*8 x, xmin, xmax, delx, f1, f2
  integer nx, i

  !assign values to variables like, xmin (the starting point of the graph)
  !xmax (the final point of the graph), nx (number of points in the graph)
  !delx (the rate of change between points in the graph)

  xmin = 0.0
  xmax = 50.0
  nx = 100
  delx = (xmax - xmin)/dfloat(nx - 1)

  !.dat is a data file
  open (unit=1, file='graph1.dat')
  open (unit=2, file='graph2.dat')

  do i = 0, nx-1
     x = xmin + dfloat(i) * delx

     write(1,*) x, f1(x)
     write(2,*) x, f2(x)
  end do

  close(1)
  close(2)

  call system('bin/graph_app graph1.dat graph2.dat')

end program main

real*8 function f1(x)
  implicit none

  real*8 x
  f1 = sqrt(x)

  return

end function

real*8 function f2(x)
  implicit none

  real*8 x
  f2 = sqrt(x) + 2

  return

end function
