var
    N, a, b, c, d, e, f, i, j, x, y, z:smallint;
begin
    readln(N);
    for N := N downto 1 do
    begin
        readln(a, b, c, d, e, f);
        z := 0;
        for i:= 1 to e do
        begin
            if (((e - i * a) mod c) = 0) then
            begin
                j := (e - i * a) div c;
                if ((i * b + j * d = f) and (j > 0)) then
                begin
                    x := i;
                    y := j;
                    z := z + 1;
                end
            end
        end;
        if (z = 1) then
            writeln(x,' ', y)
        else
            writeln('?');
    end;
end.
