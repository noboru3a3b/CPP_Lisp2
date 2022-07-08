//
//  primes (scala2)
//
// Compile: scalac primes.scala
//       -> primes$.class
//          primes.class
//
// Execute: scala primes

import scala.collection.mutable.ListBuffer

object primes
{
  var primes = ListBuffer[Int]()

  def main(args :Array[String]) :Unit =
  {
//    (3 to 1000000000 by 2).foreach {n => // このサイズではjava.lang.OutOfMemoryErrorになる！
    (3 to 100000000 by 2).foreach {n =>

      if (isPrime(n))
        primes += n
    }
//    println(2 +=: primes)
  }

  def isPrime(n :Int) :Boolean =
  {
    primes.foreach {p =>
      if ((p * p) > n)
        return true
      if ((n % p) == 0)
        return false
    }
    return true
  }
}
