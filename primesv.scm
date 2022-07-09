;; for Scheme (gauche/ypsilon/guile/chez)
;(define plen 5761455)  ; 2 .. 100000000 OK
(define plen 50847534)  ; 2 .. 1000000000 OK
(define pidx 1)
(define pi 1)
(define px 3)
(define pvect (make-vector plen 0))
(define ppvect (make-vector plen 0))

(define (primeset)
  (if (= pidx plen) #f
    (begin (vector-set! pvect pidx px)
           (vector-set! ppvect pidx (* px px))
           (set! pidx (+ pidx 1)))))

(define (is-prime)
  (set! pi 1)
  (do ((rtn 0))
      ((not (eqv? rtn 0)) rtn)
    (cond ((= (vector-ref pvect pi) 0) (set! rtn #t))
          ((> (vector-ref ppvect pi) px) (set! rtn #t))
          ((= (modulo px (vector-ref pvect pi)) 0) (set! rtn #f))
          (else (set! pi (+ pi 1))))))

(define (primes)
  (do ((rtn 0))
      ((not (eqv? rtn 0)) rtn)
    (if (is-prime)
          (if (primeset) #t
              (begin (vector-set! pvect 0 2)
                     (set! rtn pvect))))
    (set! px (+ px 2))))

(primes)
