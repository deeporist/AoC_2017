#lang racket
(define check
  (lambda (lat)
    (cond
      ((null? (cdr lat)) 1)
      ((repa (car lat) (cdr lat)) (check (cdr lat)))
      (else 0)
      )))
;;;;;;;;;;;;;;
(define repa
  (lambda (s lat)
    (cond
      ((null? lat) #t)
      ((not (string-contains? (car lat) s)) (repa s (cdr lat)))
      (else #f)
      )))
;;;;;;;;;;;;;;;;;;;;;;;
(call-with-input-file "Day4.txt"
  (lambda (input-port)
    (let loop ((x (read-line input-port))
               (sum 0)
               )
      (if (not (eof-object? x))
          (loop (read-line input-port) (+ sum (check (string-split x))))
          (display sum)
          )
      )))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
