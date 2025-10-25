module euler_angle
  implicit none
  PRIVATE
  PUBLIC::euler_to_matrix, matrix_to_euler, &
          euler_to_quaternion, quaternion_to_euler

contains
  pure subroutine euler_to_matrix(phi, theta, psi, axis1, axis2, axis3, R)
    REAL(KIND=8), INTENT(IN)    :: phi, theta, psi
    INTEGER(KIND=4), INTENT(IN) :: axis1, axis2, axis3
    REAL(KIND=8), INTENT(OUT)   :: R(3,3)

  end subroutine euler_to_matrix

  pure subroutine matrix_to_euler() 
  end subroutine matrix_to_euler

  pure subroutine euler_to_quaternion()
  end subroutine euler_to_quaternion

  pure subroutine quaternion_to_euler()
  end subroutine quaternion_to_euler
end module euler_angle
