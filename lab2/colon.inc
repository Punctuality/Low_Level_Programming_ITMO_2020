%define last_address 0

%macro colon 2
%2:
  dq last_address
  db %1, 0
%define last_address %2
%endmacro