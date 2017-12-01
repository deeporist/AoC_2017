#lang racket
(define Day1
  (lambda (s a)
    (cond 
     ((null? (cdr s)) (cond
                        ((eq? a (car s)) a)
                        (else (quote 0))))
     ((eq? (car s) (car (cdr s))) (+ (car s) (Day1 (cdr s) a)))
     (else (Day1 (cdr s) a))
     )))
;;
(call-with-input-file "Day1.txt"
  (lambda (input-port)
    (let loop ((x (read-char input-port))
               (result '()))
      (if (eof-object? x)
          (Day1 result (car result))
          (loop (read-char input-port) (cons (string->number (string x)) result)))
      
      )
      ))