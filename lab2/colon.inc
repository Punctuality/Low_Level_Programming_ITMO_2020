%define l 0

%macro colon 2
%2:
  dq l
  db %1, 0
%define l %2
%endmacro