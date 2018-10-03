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
(define s (quote (1 1 1 1)))
(define a (car s))
(Day1 s a)
;;;;;;;;;;;;;;;;;;;;;;;;
;;(call-with-input-file "Day1.txt"
;;  (lambda (input-port)
;;    (let loop ((x (read-char input-port)))
;;      (if (not (eof-object? x))
;;          (begin
;;            (display x)
;;            (loop (read-char input-port))
;;            )
;;          (close-input-port input-port))
;;      )))
;;;;;;;;;;;;;;;;;;;;;;;;;
(call-with-input-file "Day1.txt"
  (lambda (in)
    (read-line in)
    (close-input-port in)))
;;;;;;;;;;;;;;;;;;;;;;;;
(define filename "Day1.txt")
(define raw-data (with-input-from-file filename read))
;;;;;;;;;;;;;;;;;;;;;;;;
(call-with-input-file "Day1.txt"
  (lambda (input-port)
    (let loop ((x (read-char input-port))
               (result '()))
      (if (eof-object? x)
          (Day1 result (car result))
          (loop (read-char input-port) (cons (string->number (string x)) result)))
      
      )
      ))
;;;;;;;;;;;;;;;;;;;;;;;
(string->number (string #\3))
;;;;;;;;;;;;;;;;;;;;;;;
;;(+ (max lat) (min lat))
;;;;;;;;;;;;;;;;;
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
;;
;;(define tl '(bdwdjjo avricm cjbmj avricm ran lmfsom ivsof))
;;(check tl)
;;;;;;;;;;;;;;;;;;;;;;;
(call-with-input-file "Day4.txt"
  (lambda (input-port)
    (let loop ((x (read-line input-port))
               (sum 0)
               )
      (if (not (eof-object? x))
          (begin
            (display (check (string-split x)))
            (loop (read-line input-port) (+ sum (check (string-split x))))
            )
          (display sum)
          )
      )))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
