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
              ((zerop (mod x p)) nil)
              (t (is-prime (cdr p-list) x))))))

(defun primes (queue x max)
  (cond ((gt x max)
         (cons 2 (get-list queue)))
        ((is-prime (get-list queue) x)
         (primes (en-queue queue x) (add x 2) max))
        (t (primes queue (add x 2) max))))

(primes (make-queue) 3 1000)

(defun make-pvect ()
  (setq plen 100)
  (setq pidx 1)
  (setq pvect (make-vector plen 0)))

(defun primeset (x)
  (if (eqn pidx plen) nil
      (seq (vset pvect pidx x)
           (incq pidx))))

(defun is-prime (x i)
  (let ((p (vref pvect i)))
    (cond ((zerop p) t)
          ((gt (mul p p) x) t)
          ((zerop (mod x p)) nil)
          (t (is-prime x (inc i))))))

(defun primes (x)
  (if (is-prime x 1)
        (if (primeset x) (primes (add x 2))
            (seq (vset pvect 0 2) pvect))
      (primes (add x 2))))

(make-pvect)
(primes 3)

(setq IN_FILE "sample.lisp")
(setq SPLIT_LIST (split-string IN_FILE "."))
(setq OUT_FILE (concat (car SPLIT_LIST) "." "txt"))

(mapcar #'list '(a b c d e f))
(mapcan #'list '(a b c d e f))
(mapc #'list '(a b c d e f))
(mapconcat #'symbol-name '(a b c d e f) " ")
