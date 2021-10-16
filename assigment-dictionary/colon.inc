%define list 0

%macro colon 2
    %2:
    dq list
    db %1, 0
    %define list %2
%endmacro
