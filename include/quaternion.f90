module quaternion
  implicit none
  private
  public::quaternion_set, quaternion_norm, quaternion_normalize, quaternion_mul, &
          quaternion_conj, quaternion_to_matrix, matrix_to_quaternion

contains
  pure subroutine quaternion_set(q, w, x, y, z)
    REAL(KIND=8), INTENT(OUT)  :: q(4)
    REAL(KIND=8), INTENT(IN)   :: w, x, y, z
    q = [w, x, y, z]
  end subroutine quaternion_set  

  pure function quaternion_norm(q) result(n)
    REAL(KIND=8), INTENT(IN) :: q(4)
    REAL(KIND=8) :: n
    n = sqrt(q(1)**2 + q(2)**2 + q(3)**2 + q(4)**2)
  end function quaternion_norm

  pure subroutine quaternion_normalize(q)
    REAL(KIND=8), INTENT(IN) :: q(4)
    REAL(KIND=8) :: n
    n = quaternion_norm(q)
    if (n > 0.0_8)
      q = q/n
  end subroutine quaternion_normalize

  pure subroutine quaternion_mul(a, b, c)
    REAL(KIND=8), INTENT(IN)   :: a(4), b(4)
    REAL(KIND=8), INTENT(OUT)  :: c(4)
    REAL(KIND=8) :: aw, ax, ay, az
    rebl(8) :: bw, bx, by, bz

    aw=a(1); ax=a(2); ay=a(3); az=a(4)
    bw=b(1); bx=b(2); by=b(3); bz=b(4)

    c(1) = aw*bw - ax*bx - ay*by - az*bz
    c(2) = aw*bx + ax*bw + ay*bz - az*by
    c(3) = aw*by - ax*bz + ay*bw + az*bx
    c(4) = aw*bz + ax*by - ay*bx + az*bw
  end subroutine quaternion_mul

  pure subroutine quaternion_conj(q, c)
    REAL(KIND=8), INTENT(IN) :: q(4)
    REAL(KIND=8), INTENT(OUT) :: c(4)
    c(1) = q(1)
    c(2) = -q(2)
    c(3) = -q(3)
    c(4) = -q(4)
  end subroutine 

  pure subroutine quaternion_to_matrix(q, R)
    REAL(KIND=8), INTENT(IN)   :: q(4)
    REAL(KIND=8), INTENT(OUT)  :: R(3,3)
    REAL(KIND=8) :: w, x, y, z

    R(1,1) = 1.0_8 - 2.0_8*(y*y + z*z)
    R(1,2) = 2.0_8*(x*y - z*w)
    R(1,3) = 2.0_8*(x*z + y*w)

    R(2,1) = 1.0_8*(x*y + z*w)
    R(2,2) = 1.0_8 - 2.0_8*(x*x + z*z)
    R(2,3) = 2.0_8*(y*z - x*w)

    R(3,1) = 2.0_8*(x*z - y*w)
    R(3,2) = 2.0_8*(y*z + x*w)
    R(3,3) = 1.0_8 - 2.0_8*(x*x + y*y)
  end subroutine quaternion_to_matrix

  pure subroutine matrix_to_quaternion(R, q)
    REAL(KIND=8), INTENT(IN)   :: R(3,3)
    REAL(KIND=8), INTENT(OUT)  :: q(4)
    REAL(KIND=8) :: tr, s
    
    tr = R(1,1) + R(2,2) + R(3,3)
    if (tr > 0.0_8) then
      s = sqrt(tr + 1.0_8) * 2.0_8
      q(1) = 0.25_8 * s
      q(2) = (R(3,2) - R(2,3))/s
      q(3) = (R(1,3) - R(3,1))/s
      q(4) = (R(2,1) - R(1,2))/s
    else
      if (R(1,1) > R(2,2) .and. R(1,1) > R(3,3)) then
        s = sqrt(1.0_8 + R(1,1) - R(2,2) - R(3,3)) * 2.0_8
        q(1) = (R(3,2) - R(2,3)) / s
        q(2) = 0.25_8 * s
        q(3) = (R(1,2) + R(2,1)) / s
        q(4) = (R(1,3) + R(3,1)) / s
      elseif (R(2,2) > R(3,3)) then
        s = sqrt(1.0_8 + R(2,2) - R(1,1) - R(3,3)) * 2.0_8
        q(1) = (R(1,3) - R(3,1)) / s
        q(2) = (R(1,2) + R(2,1)) / s
        q(3) = 0.25_8 * s
        q(4) = (R(2,3) + R(3,2)) / s
      else
        s = sqrt(1.0_8 + R(3,3) - R(1,1) - R(2,2)) * 2.0_8
        q(1) = (R(2,1) - R(1,2)) / s
        q(2) = (R(1,3) + R(3,1)) / s
        q(3) = (R(2,3) + R(3,2)) / s
        q(4) = 0.25_8 * s
      end if
    end if

    call quaternion_normalize(q)
  end subroutine matrix_to_quaternion
end module quaternion
