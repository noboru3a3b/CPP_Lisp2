;; for Ikarus
(import (ikarus))

;; for Larceny
;(import (larceny r7r6))

(define plen 5761455)
(define pidx 1)
(define pvect (make-vector plen 0))
(define ppvect (make-vector plen 0))

(define (primeset x)
  (if (= pidx plen) #f
    (begin (vector-set! pvect pidx x)
           (vector-set! ppvect pidx (* x x))
           (set! pidx (+ pidx 1)))))

(define (is-prime x)
  (do ((pi 1 (+ pi 1))
       (rtn 0))
      ((or (= (vector-ref pvect pi) 0) (not (eqv? rtn 0))) rtn)
    (cond ((> (vector-ref ppvect pi) x) (set! rtn #t))
          ((= (modulo x (vector-ref pvect pi)) 0) (set! rtn #f)))))

(define (primes)
  (do ((rtn 0)
       (x 3 (+ x 2)))
      ((not (eqv? rtn 0)) rtn)
     (if (is-prime x)
           (if (primeset x) #t
             (begin (vector-set! pvect 0 2)
                    (set! rtn pvect))))))

(primes)
