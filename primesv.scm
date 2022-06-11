;; for Scheme (gauche/ypsilon/guile/chez)
(define plen 5761455)
(define pidx 1)
(define pi 1)
(define pvect (make-vector plen 0))
(define ppvect (make-vector plen 0))

(define (primeset x)
  (if (= pidx plen) #f
    (begin (vector-set! pvect pidx x)
           (vector-set! ppvect pidx (* x x))
           (set! pidx (+ pidx 1)))))

(define (is-prime x)
  (set! pi 1)
  (do ((rtn 0))
      ((not (eqv? rtn 0)) rtn)
    (cond ((= (vector-ref pvect pi) 0) (set! rtn #t))
          ((> (vector-ref ppvect pi) x) (set! rtn #t))
          ((= (modulo x (vector-ref pvect pi)) 0) (set! rtn #f))
          (else (set! pi (+ pi 1))))))

(define (primes)
  (do ((rtn 0)
       (x 3 (+ x 2)))
      ((not (eqv? rtn 0)) rtn)
     (if (is-prime x)
           (if (primeset x) #t
             (begin (vector-set! pvect 0 2)
                    (set! rtn pvect))))))

(primes)
