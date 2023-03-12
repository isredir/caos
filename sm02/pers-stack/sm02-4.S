	.data
stack: .skip 4 * 2000

  .text
  .global main
main:
  mov $stack, %ecx 			 #начало стека стеков
  xor %edx, %edx 			 #счетчик по массиву стеков
  xor %edi, %edi 			 #счетчик внутри стека
  movl $-1, (%ecx, %edi, 4)  #кладем -1 в нулевой стек
  inc %edi
  inc %edx

loop:
  call readi32
  jc finale
  mov %edx, %edi 			 #обновляем счетчик
  sal $1, %edi
  cmp $0, %eax 				 #проверка на операции
  jne pop_stack
  
push_stack:
  call readi32 				 #читаем номер предка
  mov %eax, (%ecx, %edi, 4)  #кладем номер предка
  call readi32 				 #читаем число
  mov %eax, 4(%ecx, %edi, 4) #кладем само число
  jmp after

pop_stack:
  call readi32 				 #читаем номер предка
  
  mov %eax, %ebx
  sal $1, %ebx
  
  mov (%ecx, %ebx, 4), %eax  #предок предка
  
  cmp $0, %eax
  jge greater
  
  dec %edx
  call writei32
  movl $-1, (%ecx, %edi, 4)  #кладем -1 если стек пустой
  jmp after
  
greater:
  
  mov %eax, %esi
  sal $1, %esi
  mov 4(%ecx, %ebx, 4), %eax #последнее число предка предка
  call writei32				 #печатаем, что мы попнули
  mov (%ecx, %esi, 4), %eax  #предок предка предка
  mov %eax, (%ecx, %edi, 4)  #кладем его номер
  mov 4(%ecx, %esi, 4), %eax #последнее число предка предка предка
  mov %eax, 4(%ecx, %edi, 4) #кладем его
  
after:
  inc %edx #увеличиваем счетчик
  jmp loop
finale:
  call finish
