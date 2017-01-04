var
    R, C:longint;
begin
    readln(R);
    readln(C);
    if ((R = 1) or (C = 1) or ((R + C) mod 2 = 1)) then
        writeln('First')
    else
        writeln('Second');
end.
