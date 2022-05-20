(let ((n 0))
  (while (< n 10)
    (print n)
    (setq n (+ n 1))))

(let* ((x 10)
       (y (* 2 x)))
  (print x)
  (print y)
  (cons x y))


(defun sqr+0 (x y)
  (if (null x) y
      (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))

(defun sqr+ (x)
  (sqr+0 x 0))

(sqr+ '(1 2 3 4 5))


(defun make-variable-c ()
  (let ((c 0))
    (list
      (closure () c)
      (closure () (setq c (+ c 1)))
      (closure () (setq c (- c 1))))))

(let* ((funcs (make-variable-c))
       (get-c (car funcs))
       (inc-c (cadr funcs))
       (dec-c (caddr funcs)))
  (print (funcall get-c))
  (funcall inc-c)
  (print (funcall get-c))
  (funcall dec-c)
  (print (funcall get-c)))


(defun make-queue ()
  (let ((queue (cons nil nil)))
    (setcar queue queue)
    queue))

(defun en-queue (queue x)
  (let ((q (cons x nil)))
    (setcdr (car queue) q)
    (setcar queue q)
    queue))

(defun get-list (queue) (cdr queue))

(defun is-prime (p-list x)
  (if (null p-list) t
      (let ((p (car p-list)))
        (cond ((gt (mul p p) x) t)
              ((eqn 0 (mod x p)) nil)
              (t (is-prime (cdr p-list) x))))))

(defun primes (queue x max)
  (cond ((gt x max)
         (cons 2 (get-list queue)))
        ((is-prime (get-list queue) x)
         (primes (en-queue queue x) (add x 2) max))
        (t (primes queue (add x 2) max))))

(primes (make-queue) 3 1000)

