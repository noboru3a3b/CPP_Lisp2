;;;    primesq2

(import (rnrs) (rnrs mutable-pairs))

;; new queue
(define (make-queue)
  (let ((queue (cons '() '())))
    (set-car! queue queue)
    queue))

(define (en-queue! queue x)
  (let ((q (cons x '())))
    (set-cdr! (car queue) q)
    (set-car! queue q)
    queue))

(define (de-queue! queue)
  (let* ((lst (cdr queue))
         (val (car lst))
         (rest (cdr lst)))
    (set-cdr! queue rest)
    (if (null? rest)
	(set-car! queue queue))
    val))

(define (get-list queue) (cdr queue))

;; primes
(define (is-prime p-lst x)
  (if (null? p-lst) #t
      (let ((p (car p-lst)))
	(cond ((> (* p p) x) #t)
	      ((= 0 (mod x p)) #f)
	      (else (is-prime (cdr p-lst) x))))))

(define (primes queue x xmax)
  (cond ((> x xmax)
	 (get-list queue))
	((is-prime (get-list queue) x)
	 (primes (en-queue! queue x) (+ x 2) xmax))
	(else
	 (primes queue (+ x 2) xmax))))

;; main
;(cons 2 (primes (make-queue) 3 100000000))
(display (length (cons 2 (primes (make-queue) 3 1000000000))))

